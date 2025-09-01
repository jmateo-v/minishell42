/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:19:26 by rafael-m          #+#    #+#             */
/*   Updated: 2025/09/01 17:09:45 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc_len(char *line)
{
	char	redir;
	int		i;
	int		len;
	
	i = 0;
	while (i < ft_strlen(line) && i < 2 && ft_strchr(REDIR_S, line[i]))
		i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (ft_strchr(QUOTES, line[i]))
	{
		len = ft_quoted_len(line + i, line[i]);
		if (len < 0)
			return (-1);
		i += len;
	}
	while (line [i])
	{		
		if (ft_strchr(SEP_STR, line [i]))
			return (i);
		i++;
	}
	return (i);
}

char	*ft_expand_heredoc(int option, t_cli *cli)
{
	char	*t;

	t = NULL;
	if (option)
	{
		t = ft_expand_line(cli->heredoc);
		if (!t)
			return (NULL);
		cli->heredoc = t;
	}
	return (cli->heredoc);
}

void	ft_here_error(char *delim)
{
	char	*t;
	char	*error_msg;

	// if (!delim)
	// 	return ;
	t = ft_strjoin(HERE_ERR, delim);
	error_msg = ft_strjoin(t, "')\n");
	if (!error_msg)
	{
		perror("malloc : ");
		return ;
	}
	write(2, error_msg, ft_strlen(error_msg));
	free(error_msg);
	free(t);
	return ;
}

char	*ft_heredoc_op(char *line, char op)
{
	char	*new_line;
	char	*t;
	int		i;

	if (!line)
		return (NULL);
	new_line = NULL;
	while (1)
	{
		i = 0;
		free(new_line);
		new_line = readline("> ");
		if (g_sigint_received)
			return (free(new_line), line);
		if (!new_line)
			return (free(line), line = NULL, write(2, HERE_PIPE_ERR, 53), NULL);
		while (new_line && ft_isspace(new_line[i]))
			i++;
		if (!new_line[i] || new_line[i] == '\n')
			continue ;
		t = ft_strjoin(line, new_line);
		free(line);
		line = t;
		if (ft_strchr(OP_STR2, line[ft_strlen(line) - 1]))
			continue ;
		break ;
	}
	return (free(new_line), line);
}

int	ft_heredoc(char *token, t_cli *cli)
{
	char	*delim;
	char	*t;
	char	*line;
	int		option;

	if (!token || !cli)
		return (0);
	delim = ft_trim_delim(token, &option);
	free(cli->heredoc);
	free(cli->infile);
	cli->infile = NULL;
	cli->heredoc = NULL;
	if (!delim)
		return (0);
	line = NULL;
	option = 0;
	while (1)
	{
		free(line);
		line = readline("> ");
		if (g_sigint_received)
			return (free(line), free(delim), write(2, "sig received in hd\n", 20), ft_set_sig(PARENT), g_sigint_received = 0, -1);
		if (!line || !ft_strcmp(line, delim))
			break ;
		t = ft_strjoin(cli->heredoc, line);
		free(cli->heredoc);
		cli->heredoc = ft_strjoin(t, "\n");
		free(t);
	}
	rl_done = 0;
	if (!line)
		ft_here_error(delim);
	cli->heredoc = ft_expand_heredoc(option, cli);
	// printf("hd = %s\n", cli->heredoc);
	return (free(line), free(delim), 1);
}