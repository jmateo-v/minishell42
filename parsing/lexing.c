/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rms35 <rms35@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:45 by rafael-m          #+#    #+#             */
/*   Updated: 2025/09/20 15:43:11 by rms35            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_quoted_len(char *line, char quote)
{
	int	i;

	if (!line)
		return (0);
	i = 1;
	while (line[i])
	{
		if (line[i] == quote)
		{
			if(quote == '\'')
				return (i + 1);
			else if (quote == '\"')
			{
				if (line[i - 1] != '\\')
					return (i + 1);
			}
		}
		i++;
	}
	return (-1);
}

char	*ft_escaped_line(char *line, int start, int end)
{
	char	*escaped;
	char	*t;
	char	*s;

	if (!line || start < 0 || end < start)
		return (NULL);
	if (end == 0)
		return (ft_strdup(line));
	escaped = ft_esc_str(line + start + 1, ESC_CHARS1, end - start - 2);
	t = ft_strndup(line, start);
	if (!escaped)
		return (NULL);
	s = ft_strjoin(t, escaped);
	if (!s)
		return (NULL);
	free(escaped);
	free(t);
	t = ft_strjoin(s, line + end);
	free(s);
	return (s = NULL, escaped = NULL, t);
}

char *ft_esc_line(char *line, int i, int len)
{
	char	*esc_line;
	char	*t;

	if (ft_strchr(QUOTES, line[i]) && line[i] == line[i + 1])
	{
		t = ft_strndup(line, i);
		if (i > 0 && !t)
			return (perror("malloc1 : "), NULL);
		if (!line[i + 2])
			return (t);
		esc_line = ft_strjoin(t, line + i + 2);
		if (esc_line != t)
		{
			free(t);
			t = NULL;
		}
		if (!esc_line)
			return (perror("malloc : "), NULL);
		return (esc_line);
	}
	esc_line = ft_escaped_line(line, i, len);
	return (esc_line);
}

char	*ft_escape_quotes(char *line)
{
	int		i;
	int		len;
	char	*esc_line;
	char	*s;

	if (!line)
		return (NULL);
	i = 0;
	s = ft_strdup(line);
	while (i < ft_strlen(s))
	{
		if (ft_strchr(QUOTES, s[i]) && (i == 0 || (i > 0 && line[i - 1] != '\\')))
		{
			len = ft_quoted_len(s + i,  s[i]);
			if (len < 0)
				return (free(s), NULL);
			esc_line = ft_esc_line(s, i , i + len);
			if (!esc_line)
				return (free(s), NULL);
			i += (len - 2);
			free(s);
			s = esc_line;
			continue ;
		}
		i++;
	}
	return (s);
}

char	**ft_tokens(char *line, t_shenv *env, t_cli *cli)
{
	char	**tokens;

	if (!line)
		return (NULL);
	if (ft_check_prnts(line))
		return (printf("prnts error\n"), NULL);
	cli->n_tokens = ft_num_s_tokens(line);
	tokens = ft_token_sep(ft_trim_spaces(line));
	if (!tokens)
		return (NULL);
	tokens = ft_expand_tokens(tokens, &(cli->n_tokens), cli);
	if (!tokens)
		return (ft_free_tokens(tokens, cli->n_tokens), NULL);
	if (ft_check_errors(tokens, cli->n_tokens))
		return (ft_free_tokens(tokens, cli->n_tokens), NULL);
	return (tokens);
}
