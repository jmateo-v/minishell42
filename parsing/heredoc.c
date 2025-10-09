/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:19:26 by rafael-m          #+#    #+#             */
/*   Updated: 2025/10/09 16:39:00 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc_len(char *line)
{
	int		i;
	int		len;
	
	i = 0;
	while (i < (int)ft_strlen(line) && i < 2 && ft_strchr(REDIR_S, line[i]))
		i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (i < (int)ft_strlen(line) && line[i])
	{
		if (i < (int)ft_strlen(line) && ft_strchr(QUOTES, line[i])  && (i == 0 || (i > 0 && line[i - 1] != '\\')))
		{
			len = ft_quoted_len(line + i, line[i]);
			if (len <= 0)
				return (-1);
			i += (len + 1);
			continue ;
		}	
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
	if (option && cli->heredoc)
	{
		t = ft_expand_line(cli->heredoc, cli);
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

static void	ft_free_prev(t_cli *cli)
{
	free(cli->heredoc);
	free(cli->infile);
	cli->infile = NULL;
	cli->heredoc = NULL;
}

static int	ft_read_heredoc(t_cli *cli, int *option, char *delim)
{
	char	*line;
	char	*t;
	char buffer[1024];
	ssize_t		bytes_read;

	line = NULL;
	if (!cli->heredoc)
		cli->heredoc = ft_strdup("");
	while (1)
	{
		if (line)
		{
		free(line);
		line = NULL;
		}
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
		{
			bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
			if (bytes_read <= 0)
			{
				break;
			}
			buffer[bytes_read] = '\0';
			line = ft_strdup(buffer);
		}
		if (g_sig_rec)
			return (free(line), free(delim), cli->status = 130, 130);
		if (!line)
			return(ft_here_error(delim), free(delim), 0);
		if (!ft_strcmp(line, delim))
		{
			break ;
		}
		t = ft_strjoin(cli->heredoc, line);
		free(cli->heredoc);
		cli->heredoc = ft_strjoin(t, "\n");
		free(t);
	}
	if (cli->heredoc)
	{
    	cli->heredoc = ft_expand_heredoc(*option, cli);
    	if (!cli->heredoc)
        	return (free(line), free(delim), cli->status = 2, 2);
	}
	return (free(line), free(delim), 0);
}

int	ft_heredoc(char *token, t_cli *cli)
{
	char	*delim;
	int		option;
	int		status;

	if (!cli)
		return (printf("!cli\n"), 2);
	ft_free_prev(cli);
	if (!token)
		return (ft_perror("<<", SYN_ERR), 2);
	delim = ft_trim_delim(token, &option);
	if (!delim)
		return (cli->status = 2, 2);
	option = 0;
	status = ft_read_heredoc(cli, &option, delim);
	if (status == 130)
	{
		ft_set_sig(PARENT);
		g_sig_rec = 0;
	}
	return (status);
}