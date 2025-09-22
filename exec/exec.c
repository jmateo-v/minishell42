/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:37:18 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/09/22 15:04:29 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_execute(t_cli *cli)
{
    int last_status;

    last_status = 0; 
    if (!cli || !cli->cmd)
        return (perror("!cmd"), 127);
    if (has_pipes_or_redirs(cli))
        last_status = execute_pipeline(cli);
    else if (cli->is_builtin)
        last_status = execute_builtin(cli);
    else
        last_status = execute_command(cli);
    return (last_status);
}
int execute_command(t_cli *cmd)
{
    pid_t   pid;
    char    **env;

    if (!cmd || !cmd->cmd)
        return (-1);
    ft_set_sig(IGNORE);
    pid = fork();
    if (pid == 0)
    {
        ft_set_sig(CHILD);
        env = ft_getshenv(*(cmd->env));
        if (!env && cmd->env)
            exit(2);
        execve(cmd->cmd, cmd->args, env);
        ft_free_env(cmd->env);
        ft_free_d(env);
        ft_free_list(&cmd);
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
    char    **env;

    if (!cmd || !cmd->cmd)
        return (printf("!cmd"), 1);
    if (!ft_strcmp(cmd->cmd, "pwd"))
        return (ft_pwd(cmd->args));
    else if (!ft_strcmp(cmd->cmd, "cd"))
        return (ft_cd(cmd->args, cmd->env));
    else if (!ft_strcmp(cmd->cmd, "echo"))
        return (ft_echo(cmd->args));
    else if (!ft_strcmp(cmd->cmd, "export"))
        return(ft_export(cmd->args,  cmd->env));
    else if (!ft_strcmp(cmd->cmd, "unset"))
        return(ft_unset(cmd->args, cmd->env));
    else if (!ft_strcmp(cmd->cmd, "env"))
    {
        env = ft_getshenv(*(cmd->env));
        if (!env && cmd->env)
            return (ft_putstr_fd("minishell: env: failed to retrieve environment\n", 2), 1);
        return (ft_env(env));
    }
    else if (!ft_strcmp(cmd->cmd, "exit"))
        return (ft_exit());
    return (1);
}


