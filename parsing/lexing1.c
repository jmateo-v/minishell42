/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:55 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/27 16:49:19 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_lex_pipe(char **token, int *len)
{
	char	**t;
	char	**s;
	int		spaces;
	int		i;

	if (!token || !len || *len <= 0)
		return (NULL);
	i = 0;
	while (token[i])
	{
		if (token[i][0] == '|' && token[i][1])
		{
			spaces = 1;
			t = (char **)ft_add_re_ptr((void **)token, "|", i);
			while (ft_isspace(token[i][spaces]))
				spaces++;
			s = (char **)ft_add_ptr((void **)t, token[i] + spaces, i + 1);
			if (!t || ! s)
				return (ft_free_d(s), ft_free_d(t), NULL);
			ft_free_tokens(token, *len);
			ft_free_tokens(t, *len);
			token = s;
			*len++;
		}
		i++;
	}
	return (token);
}

int	ft_sep_len(char *line)
{
	int	i;
	int	len;

	if (!line)
		return (0);
	i = 0;
	len = ft_strlen(line);
	while (i < len && ft_isspace(line[i]))
		i++;
	if (ft_strchr(REDIR_S, line[i]))
		return (ft_heredoc_len(line + i));
	while (i < len)
	{
		if (ft_strchr(QUOTES, line[i]))
		{
			if (ft_quoted_len(line + i, line[i]) < 0)
				return (printf("sep_len error\n"), -1);
			i = (ft_quoted_len(line + i, line[i]) + i);
			continue ;
		}
		if (ft_strchr(SEP_STR, line[i]) && i != 0)
			return (i);
		i++;
	}
	return (i);
}

int	ft_num_s_tokens(char *line)
{
	int	i;
	int	len;
	int	line_len;
	int	token_num;

	if (!line)
		return (0);
	i = 0;
	token_num = 0;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		len = ft_sep_len(line + i);
		if (len < 0)
			return (printf("num_s_tokens error!\n"), -1);
		i += len;
		token_num++;
		i++;
	}
	return (token_num);
}

char	**ft_token_sep(char *line)
{
	int		i;
	int		j;
	int		len;
	char	**tokens;

	if (!line)
		return (NULL);
	len = ft_num_s_tokens(line);
	if (len == -1)
		return (NULL);
	tokens = (char **)ft_calloc(len + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (tokens && i < ft_strlen(line))
	{
		while (ft_isspace(line[i]))
			i++;
		if (ft_sep_len(line + i) <= 0)
			return (tokens[len] = NULL, ft_free_d(tokens), NULL);
		tokens[j++] = ft_strndup(line + i, ft_sep_len(line + i));
		i += ft_sep_len(line + i);
	}
	return (tokens[len] = NULL, tokens);
}
