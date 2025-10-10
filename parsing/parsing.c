/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:19:42 by rafael-m          #+#    #+#             */
/*   Updated: 2025/10/10 11:13:14 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_append(char *token, t_cli *cli)
{
	int	i;

	if (!token)
		return (ft_perror(">>", SYN_ERR), 0);
	if (!cli)
		return (0);
	i = 0;
	free(cli->outfile);
	cli->r_mode = APPEND;
	cli->breaks_pipe = true;
	if (ft_strchr(QUOTES, token[i]) && (i == 0 || (i > 0 && token[i - 1] != '\\')))
		cli->outfile = ft_strndup(token + i + 1, ft_strlen(token) - i - 2);
	else
		cli->outfile = ft_strdup(token + i);
	if (!cli->outfile)
		return (perror("malloc : "), 0);
	return (1);
}

int	ft_outfile(char *token, t_cli *cli)
{
	int	i;

	if (!token)
		return (ft_perror(">", SYN_ERR), 0);
	if (!cli)
		return (0);
	i = 0;
	free(cli->outfile);
	cli->r_mode = 0;
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

	if (!cli)
		return (0);
	i = 0;
	if (!token)
		return (ft_perror("<", SYN_ERR), 0);
	free(cli->infile);
	free(cli->heredoc);
	cli->heredoc = NULL;
	if (ft_strchr(QUOTES, token[i]) && (i == 0 || (i > 0 && token[i - 1] != '\\')))
		cli->infile = ft_strndup(token + i + 1, ft_strlen(token) - i - 2);
	else
		cli->infile = ft_strdup(token + i);
	if (!cli->infile)
		return (0);
	return (1);
}

int	ft_parse_token(t_token *token, int i, t_cli *cli, int *group)
{
	if (token[i].value && token[i].value[0] == '(')
		(*group)++;
	else if (token[i].value && token[i].value[0] == ')')
	{
		(*group)--;
		cli->op = 0;
	}
	else if (token[i].value && !cli->cmd)
	{
		ft_cmd(token[i].value, cli);
		ft_args(token[i].value, cli, ft_doubleptr_len((void **)cli->args));

		cli->group = *group;
	}
	else
	{
		ft_args(token[i].value, cli, ft_doubleptr_len((void **)cli->args));
	}

	return (i);
}

int	ft_parse(t_token *tokens, t_cli *cli)
{
	int		i;
	int		len;
	int		group;

	if (!tokens || !cli)
		return (2);

	i = 0;
	group = 1;
	len = ft_token_count(tokens);
	cli->n_tokens = 1;
	while (i < len)
	{
		if (tokens[i].value && tokens[i].value[0] == '\0')
		{
			i++;
			continue;
		}
		if (tokens[i].value && !ft_strncmp(tokens[i].value, ">>", 2))
		{
			if (i + 1 >= len)
				return(perror("missing target for >>, SYN ERR"), ft_free_tokens(tokens), 2);
			ft_append(tokens[i + 1].value, cli);
			i += 2;
			continue;
		}
		else if (tokens[i].value && !ft_strncmp(tokens[i].value, "<<", 2))
		{
			if (i + 1 >= len)
            	return (ft_perror("missing target for <<", SYN_ERR), ft_free_tokens(tokens), 2);
        	if (ft_heredoc(tokens[i + 1].value, cli) == 130)
            return (ft_free_tokens(tokens), 130);
        	i += 2;
        	continue;
		}
		else if (tokens[i].value && ft_strchr(OP_STR2, tokens[i].value[0]))
		{
			cli->next = ft_parse_op(tokens[i].value, cli);
			if (!cli->next)
				return (2);
			cli = cli->next;
		}
		else
			i = ft_parse_token(tokens, i, cli, &group);
		i++;
	}
	return (0);
}


