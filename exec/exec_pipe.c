/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:21:28 by dogs              #+#    #+#             */
/*   Updated: 2025/10/06 17:33:52 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_prepare_heredoc_fd(t_cli *cli)
{
    int pipefd[2];
    if (!cli->heredoc)
        return (-1);
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    write(pipefd[1], cli->heredoc, ft_strlen(cli->heredoc));
    close(pipefd[1]);
    return (pipefd[0]);
}
int ft_prepare_all_heredocs(t_cli *cli)
{
    t_cli *current;

    current = cli;
    while (current)
    {
        if (current->heredoc)
        {
            current->heredoc_fd = ft_prepare_heredoc_fd(current);
            if (current->heredoc_fd == -1)
            {
                return(-1);
            }
        }
        current = current->next;
    }
    return (0);
}
void exit_perror(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
void    setup_child(t_cli *cmd, int prev_pipe, int *pipe_fd)
{
    int fd;
    int flags;

    if (cmd->heredoc_fd != -1)
    {
        dup2(cmd->heredoc_fd, STDIN_FILENO);
        close(cmd->heredoc_fd);
    }
    else if (cmd->infile)
    {
        fd = open(cmd->infile, O_RDONLY);
        if (fd < 0)
            exit_perror(cmd->infile);
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    else if (prev_pipe != -1)
    {
        dup2(prev_pipe, STDIN_FILENO);
        close(prev_pipe);
    }
    if (cmd->outfile)
    {
        flags = O_WRONLY | O_CREAT;
        if(cmd->r_mode == WRITE)
            flags |= O_TRUNC;
        else if (cmd->r_mode == APPEND)
            flags |= O_APPEND;
        fd = open(cmd->outfile, flags, 0644);
        if (fd < 0)
            exit_perror(cmd->outfile);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    else if (pipe_fd)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
    }
    if (prev_pipe != -1)
        close(prev_pipe);
    if (pipe_fd && pipe_fd[0] != -1)
        close(pipe_fd[0]);
}

void    exec_command(t_cli **cli)
{
    char **env;
    int status;
    t_cli   *cmd;

    cmd = *cli;
    env = ft_getshenv(*(cmd->env));
    if (cmd -> env && !env)
        exit(2);
    if (cmd->is_builtin)
    {
        status = execute_builtin(cmd);
        ft_free_env(cmd->env);
        ft_free_list(cli);
        ft_free_d(env);
        exit(status);
    }
    execve(cmd->cmd, cmd->args, env);
    perror("execve");
    ft_free_env(cmd->env);
    ft_free_list(cli);
    ft_free_d(env);
    exit(127);
}

int wait_for_children(pid_t last_pid, pid_t *child_pids, int child_count)
{
    int remaining;
    int status;
    int last_status;
    bool sigint_sent;
    pid_t wpid;

    remaining = child_count;
    last_status = 0;
    sigint_sent = false;

    while (remaining > 0)
    {
        wpid = waitpid(-1, &status, 0);
        if (wpid == -1)
        {
            if (errno == EINTR)
                continue;
            else
                break;
        }
        remaining --;
        if (wpid == last_pid)
            last_status = status;
        if (g_sig_rec && !sigint_sent)
        {
            int i = 0;
            while (i < child_count)
            {
                kill(child_pids[i], SIGINT);
                i++;
            }
            sigint_sent = true;
        }
    }
    if (WIFEXITED(last_status))
        return WEXITSTATUS(last_status);
    else if (WIFSIGNALED(last_status))
    {
        printf ("\n");
        return (128 + WTERMSIG(last_status));
    }
    return (1);
}

int execute_pipeline(t_cli *cli)
{
    t_cli *current;
    int prev_pipe;
    int pipe_fd[2];
    bool has_next;
    pid_t pid;
    pid_t last_pid;
    pid_t child_pids[MAX_CMDS];
    int child_count;
    int exit_code;

    current = cli;
    prev_pipe = -1;
    last_pid = -1;
    child_count = 0;

    ft_set_sig(IGNORE);
    if (ft_prepare_all_heredocs(cli) == -1)
        return (1);
    current = cli;
    while (current)
    {
        has_next = (current->next != NULL);
        if (has_next && pipe(pipe_fd) == -1)
            exit_perror("pipe");
        pid = fork();
        if (pid == -1)
            exit_perror("fork");
        if (pid == 0)
        {
            ft_set_sig(CHILD);
            if(has_next)
                setup_child(current, prev_pipe, pipe_fd);
            else
                setup_child(current, prev_pipe, NULL);
            exec_command(&current);
        }
        child_pids[child_count++] = pid;
        if (prev_pipe != -1)
            close(prev_pipe);
        if (current->heredoc_fd != -1)
            close(current->heredoc_fd);
        if (has_next)
        {
            close(pipe_fd[1]);
            prev_pipe = pipe_fd[0];
        }
        else
        {
            prev_pipe = -1;
            last_pid = pid;
        }
        current = current->next;
    }
    ft_set_sig(IGNORE);
    exit_code = wait_for_children(last_pid, child_pids, child_count);
    ft_set_sig(PARENT);
    return (exit_code);
}