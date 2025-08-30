/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:19:26 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/27 16:49:13 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc_len(char *line)
{
	char	redir;
	int		i;
	int		len;
	
	i = 0;
	while (ft_strchr(REDIR_S, line[i]) && i < 2)
		i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && ft_strchr(REDIR_S, line[i]))
		return (write(2, UNEX_T1, 50), -1);
	if (ft_strchr(QUOTES, line[i]))
	{
		len = ft_quoted_len(line + i, line[i]);
		if (len < 0)
			return (printf("here_len error\n"), -1);
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

	if (!delim)
		return ;
	t = ft_strjoin(HERE_ERR, delim);
	error_msg = ft_strjoin(t, "')\n");
	write(2, error_msg, ft_strlen(error_msg));
	free(error_msg);
	free(t);
	return ;
}

int	ft_heredoc(char *token, t_cli *cli)
{
	char	*delim;
	char	*t;
	char	*line;
	int		option;

	if (!token || !cli)
		return (0);
	option = 0;
	delim = ft_trim_delim(token, &option);
	free(cli->heredoc);
	free(cli->infile);
	cli->infile = NULL;
	cli->heredoc = NULL;
	if (!delim)
		return (0);
	g_sigint_received = 0;
	ft_set_sig(HERE_DOC);
	line = NULL;
	while (1)
	{
		free(line);
		line = readline("> ");
		if (g_sigint_received)
		{
			cli->status = 130;
			free(line);
			free(delim);
			ft_set_sig(PARENT);
			free(cli->heredoc);
			cli->heredoc = NULL;
			return (-1);
		}
		if (!line)
			break ;
		if (!ft_strcmp(line, delim))
			break ;
		t = ft_strjoin(cli->heredoc, line);
		free(cli->heredoc);
		cli->heredoc = ft_strjoin(t, "\n");
		free(t);
	}
	if (!line)
		ft_here_error(delim);
	cli->heredoc = ft_expand_heredoc(option, cli);
	ft_set_sig(PARENT);
	return (free(line), free(delim), 1);
}