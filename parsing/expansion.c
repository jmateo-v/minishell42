/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:24 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/31 16:19:21 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_trim_delim(char *token, int *option)
{
	char	*delim;
	int		i;

	if (!token)
		return (NULL);
	i = 0;
	while (token[i] == '<' && i < 2)
		i++;
	while (ft_isspace(token[i]))
		i++;
	if (ft_strchr(QUOTES, token[i]))
	{
		if (token[i] == '\"')
			*option = 1;
		delim = ft_strndup(token + i + 1, ft_strlen(token) - i - 2);
	}
	else
		delim = ft_strdup(token + i);
	return (delim);
}

int	ft_var_len(char	*var)
{
	int	i;
	int	len;

	if (!var)
		return (0);
	i = 1;
	len = ft_strlen(var);
	while (i < len)
	{
		if (var[i] == '?' || ft_strchr(NO_VAL_VAR, var[i]))
			return (i);
		i++;
	}
	return (i);
}

char	*ft_expand_var(char	*line, int start, int end)
{
	char	*s;
	char	*t;
	char	*var;

	if (!line)
		return (NULL);
	if (end > ft_strlen(line))
		return (ft_strndup(line, end));
	s = ft_strndup(line + start, end);
	t = ft_strtrim(s, NO_VAL_VAR);
	if (!s || !t)
		return (free(s), free(t), NULL);
	free(s);
	var = getenv(t);
	free(t);
	s = ft_strndup(line, start);
	t = ft_strjoin(s, var);
	free(s);
	s = NULL;
	s = ft_strjoin(t, line + start + end);
	free(t);
	t = NULL;
	return (s);
}
char *ft_expand_status_var(char *line, int status)
{
	char *expanded_line;
	char *status_str;
	int i;
	int j;
	int len;
	int expanded_len;
	
	i = 0;
	j = 0;
	len = 0;
	expanded_len = 0;
	if (!line)
		return NULL;
	status_str = ft_itoa(status);
	if (!status_str)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			len += ft_strlen(status_str);
			i += 2;
		}
		else
		{
			len++;
			i++;
		}
	}
	expanded_line = malloc(len + 1);
	if (!expanded_line)
	{
		free(status_str);
		return (NULL);
	}
	i = 0;
	expanded_len = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			j = 0;
			while (status_str[j] != '\0')
			{
				expanded_line[expanded_len++] = status_str[j];
				j++;
			}
			i += 2;
		}
		else
		{
			expanded_line[expanded_len++] = line[i++];
		}
	}
	expanded_line[expanded_len] = '\0';
	free(status_str);
	return expanded_line;
}

char	*ft_expand_line(char *line)
{
	int		i;
	char	*t;

	i = 0;
	while (line && i < ft_strlen(line))
	{
		if (line[i] == '\'')
			i += (ft_quoted_len(line + i, '\'') + 1);
		if (i < ft_strlen(line) && line[i] == '<' && line[i + 1] == '<')
		{
			if (ft_heredoc_len(line + i) <= 0)
				return (free(line), line = NULL, NULL);
			i += (ft_heredoc_len(line + i) - 1);
		}
		if (i < ft_strlen(line) && line[i] == '$' && line[i + 1] && !ft_strchr(NO_VAL_VAR,
				line[i + 1]) && line[i + 1] != '?')
		{
			t = ft_expand_var(line, i, ft_var_len(line + i));
			if (line != t)
				free(line);
			line = t;
		}
		i++;
	}
	t = ft_strtrim(line, " ");
	return (free(line), line = NULL, t);
}

char	**ft_expand_tokens(char **tokens, int *len)
{
	char	*t;
	// char	**piped;
	int		i;

	if (!tokens)
		return (NULL);
	i = 0;
	// piped = ft_lex_pipe(tokens, len);
	i = 0;
	while (tokens[i])
	{
		t = ft_expand_line(tokens[i]);
		tokens[i] = ft_escape_quotes(t);
		free(t);
		i++;
	}
	return (tokens);
}