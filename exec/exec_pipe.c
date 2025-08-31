/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:21:28 by dogs              #+#    #+#             */
/*   Updated: 2025/08/31 18:04:09 by dogs             ###   ########.fr       */
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
                ft_putstr_fd("Failed to prepare heredoc", 2);
                return(-1);
            }
        }
        current = current->next;
    }
    return (0);
}



int execute_pipeline(t_cli *cli)
{
    t_cli *current;
    int prev_pipe;
    int pipe_fd[2];
    pid_t pid;
    bool has_next;
    int fd_in;
    int flags;
    int fd_out;
    int status;
    int last_status;
    
    last_status = 0;
    current = cli;
    prev_pipe = -1;
    ft_set_sig(IGNORE);
    if (ft_prepare_all_heredocs(cli) == -1)
        return(1);
    current = cli;
    while (current)
    {
        has_next = (current->next != NULL);
        if (has_next)
        {
            if(pipe(pipe_fd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            ft_set_sig(CHILD);
            if (current->heredoc_fd != -1)
            {
                dup2(current->heredoc_fd, STDIN_FILENO);
                close(current->heredoc_fd);
            }
            else if (current->infile)
            {
                fd_in = open(current->infile, O_RDONLY);
                if (fd_in < 0)
                {
                    perror(current->infile);
                    exit(EXIT_FAILURE);
                }
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }
            else if (prev_pipe != -1)
            {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            if(current->outfile)
            {
                flags = O_WRONLY | O_CREAT;
                if (current->r_mode == 1)
                    flags |= O_TRUNC;
                else if (current->r_mode == 2)
                    flags |= O_APPEND;
                fd_out = open(current->outfile, flags, 0644);
                if (fd_out < 0)
                {
                    perror(current->outfile);
                    exit(EXIT_FAILURE);
                }
                dup2(fd_out, STDOUT_FILENO);
                close(fd_out);
            }
            else if (has_next)
            {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }
            if (prev_pipe != -1)
                close(prev_pipe);
            if (has_next)
                close(pipe_fd[0]);
            execve(current->cmd, current->args, current->env);
            perror("execve");
            exit(127);
        }
        else
        {
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
                prev_pipe = -1;         
        }
        current = current->next;
    }
    ft_set_sig(PARENT);
    while(wait(&status) > 0)
        last_status = status;
    return (WEXITSTATUS(last_status));
}