/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:10:00 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/27 16:49:29 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parse_pipe(char *token, t_cli *cli)
{
	char	*pipe;

	if (!token || !cli)
		return (-1);
	
}

char	*ft_cmd_path(char *env_path, char *cmd)
{
	int		i;
	char	**path;
	char	*cmd_path;
	char	*t;

	i = 0;
	path = ft_split(env_path, ':');
	if (!path)
		return (perror("malloc"), NULL);
	while (path[i])
	{
		t = ft_strjoin(path[i], "/");
		if (!t)
			return (ft_free_d(path), perror("malloc"), NULL);
		cmd_path = ft_strjoin(t, cmd);
		free(t);
		if (!cmd_path)
		    return (ft_free_d(path), perror("malloc"), NULL);
		if (!access(cmd_path, X_OK))
			return (ft_free_d(path), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_d(path), NULL);
}

void	ft_no_cmd_error(char *cmd)
{
	char	**cmd_path;
	char	*msg;
	char	*t;
	int		i;

	cmd_path = ft_split(cmd, '\\');
	i = 0;
	while (cmd_path && cmd_path[i] && cmd_path[i + 1])
		i++;
	if (cmd_path)
		t = ft_strjoin("minishell: ", cmd_path[i]);
	else
		t = ft_strdup("minishell : ");
	msg = ft_strjoin(t, CMD_ERR);
	if (cmd && (!t || !msg))
		perror("malloc");
	write(2, msg, ft_strlen(msg));
	free(t);
	free(msg);
	ft_free_d(cmd_path);
	return ;
}


int	ft_cmd(char	*token, t_cli *cli)
{
	char	*trimmed;
	
	if (!token)
		return (0);
	if (!ft_strcmp(token, "echo")
	||  !ft_strcmp(token, "cd") || !ft_strcmp(token, "pwd")
	|| !ft_strcmp(token, "export") || !ft_strcmp(token, "unset")
	|| !ft_strcmp(token, "env") || !ft_strcmp(token, "exit"))
		return (cli->is_builtin = 1, cli->cmd = ft_strdup(token), 1);
	if (ft_strchr(QUOTES, token[0]))
		trimmed = ft_strndup(token + 1, ft_strlen(token) - 1);
	else
		trimmed = ft_strdup(token);
	if (trimmed && ft_strchr(trimmed, '/'))
		cli->cmd = ft_strdup(trimmed);
	else
		cli->cmd = ft_cmd_path(getenv("PATH"), trimmed);
	if (!cli->cmd)
		cli->cmd = ft_strdup(token);
	return (free(trimmed), trimmed = NULL, 1);
}