/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:37:18 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/08/31 16:43:57 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_execute(t_cli *cli)
{
    int last_status;
    last_status = 0; 
    if (!cli || !cli->cmd)
        return ; 
    if (has_pipes_or_redirs(cli))
        last_status = execute_pipeline(cli);
    else if (cli->is_builtin)
        last_status = execute_builtin(cli);
    else
        last_status = execute_command(cli);
    return last_status;
}
int execute_command(t_cli *cmd)
{
    pid_t pid;

    if (!cmd || !cmd->cmd)
    {
        return (-1);
    }
    ft_set_sig(IGNORE);
    pid = fork();
    if (pid == 0)
    {
        ft_set_sig(CHILD);
        execve(cmd->cmd, cmd->args, cmd->env);
        perror("execve");
        exit(127);
    }
    else if (pid > 0)
    {
        waitpid(pid, &cmd->status, 0);
        ft_set_sig(PARENT);
        if (WIFSIGNALED(cmd->status))
        {
            if (WTERMSIG(cmd->status) == SIGINT)
                write(STDOUT_FILENO, "\n", 1);
            return (128 + WTERMSIG(cmd->status));
        }
        else if (WIFEXITED(cmd->status))
            return (WEXITSTATUS(cmd->status));
        else
            return (cmd->status);
    }
    else
    {
        perror("fork failed");
        ft_set_sig(PARENT);
        return (-1);
    }
}
bool has_pipes_or_redirs(t_cli *cli)
{
    while (cli)
    {
        if (cli-> infile || cli->outfile || cli->heredoc)
            return (true);
        if (cli->next)
            return (true);
        cli = cli->next;
    }
    return (false);
}

int execute_builtin(t_cli *cmd)
{
    if (!cmd || !cmd->cmd)
        return (1);

    if (!ft_strcmp(cmd->cmd, "pwd"))
        return (ft_pwd(cmd->args));
    else if (!ft_strcmp(cmd->cmd, "cd"))
        return (ft_cd(cmd->args, &cmd->env));
    else if (!ft_strcmp(cmd->cmd, "echo"))
        return (ft_echo(cmd->args));
    else if (!ft_strcmp(cmd->cmd, "export"))
        printf("NOT IMPLEMENTED\n");
    else if (!ft_strcmp(cmd->cmd, "unset"))
        printf("NOT IMPLEMENTED\n");
    else if (!ft_strcmp(cmd->cmd, "env"))
        return (ft_env(cmd->env));
    else if (!ft_strcmp(cmd->cmd, "exit"))
        return (ft_exit());
    return (1);
}


