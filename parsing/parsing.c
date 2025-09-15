/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:19:42 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/21 17:13:38 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_append(char *token, t_cli *cli)
{
	int	i;

	if (!token || !cli)
		return (0);
	i = 0;
	free(cli->outfile);
	cli->r_mode = APPEND;
	while (token[i] == '>' && i < 2)
		i++;
	while (ft_isspace(token[i]))
		i++;
	if (ft_strchr(QUOTES, token[i]) && (i == 0 || (i > 0 && token[i - 1] != '\\')))
		cli->outfile = ft_strndup(token + i + 1, ft_strlen(token) - i - 2);
	else
		cli->outfile = ft_strdup(token + i);
	if (!cli->outfile)
		return (0);
	return (1);
}

int	ft_outfile(char *token, t_cli *cli)
{
	int	i;

	if (!token || !cli)
		return (0);
	i = 0;
	free(cli->outfile);
	cli->r_mode = 0;
	while (token[i] == '>' && i < 1)
		i++;
	while (ft_isspace(token[i]))
		i++;
	if (ft_strchr(QUOTES, token[i]) && (i == 0 || (i > 0 && token[i - 1] != '\\')))
		cli->outfile = ft_strndup(token + i + 1, ft_strlen(token) - i - 2);
	else
		cli->outfile = ft_strdup(token + i);
	if (!cli->outfile)
		return (0);
	return (1);
}

int	ft_infile(char *token, t_cli *cli)
{
	int	i;

	if (!token || !cli)
		return (0);
	i = 0;
	free(cli->infile);
	free(cli->heredoc);
	cli->heredoc = NULL;
	while (token[i] == '<' && i < 1)
		i++;
	while (ft_isspace(token[i]))
		i++;
	if (ft_strchr(QUOTES, token[i]) && (i == 0 || (i > 0 && token[i - 1] != '\\')))
		cli->infile = ft_strndup(token + i + 1, ft_strlen(token) - i - 2);
	else
		cli->infile = ft_strdup(token + i);
	if (!cli->infile)
		return (0);
	return (1);
}

int	ft_parse_token(char *token, t_cli *cli, int *group)
{
	if (token && token[0] == '<')
		ft_infile(token, cli);
	else if (token && token[0] == '>')
		ft_outfile(token, cli);
	else if (token && token[0] == '(')
		*group++;
	else if (token && token[0] == ')')
	{
		*group--;
		cli->op = 0;
	}
	else if (token && !cli->cmd)
	{
		ft_cmd(token, cli);
		ft_args(token, cli, ft_doubleptr_len((void **)cli->args));
		cli->group = *group;
	}
	else
		ft_args(token, cli, ft_doubleptr_len((void **)cli->args));
}

int	ft_parse(char **token, t_cli *cli)
{
	int		i;
	int		len;
	int		status;
	int		group;

	if (!token || !cli)
		return (2);
	i = 0;
	group = 1;
	len = cli->n_tokens;
	cli->n_tokens = 1;
	while (i < len)
	{
		if (token[i] && !ft_strncmp(token[i], ">>", 2))
			ft_append(token[i], cli);
		else if (token[i] && !ft_strncmp(token[i], "<<", 2))
		{
			if (ft_heredoc(token[i], cli) == 130)
				return (130);
		}
		else if (token[i] && ft_strchr(OP_STR2, token[i][0]))
		{
			cli->next = ft_parse_op(token[i], cli);
			if (!cli->next)
				return (2);
			cli = cli->next;
		}
		else
			ft_parse_token(token[i], cli, &group);
		i++;
	}
	return (ft_free_tokens(token, len), 0);
}