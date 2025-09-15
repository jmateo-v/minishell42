/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:24 by rafael-m          #+#    #+#             */
/*   Updated: 2025/09/15 14:54:57 by jmateo-v         ###   ########.fr       */
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
	if (ft_strchr(QUOTES, token[i]) && (i == 0 || (i > 0 && token[i - 1] != '\\')))
	{
		if (token[i] == '\"')
			*option = 1;
		delim = ft_escape_quotes(token + i);
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
char *ft_expand_exit_status(int status, char *line, int i)
{
	char *before;
	char *after;
	char *status_str;
	char *tmp;
	char *new_line;

	before = ft_strndup(line, i);
	after = ft_strdup(line + i + 2);
	status_str = ft_itoa(status);
	tmp = ft_strjoin(before, status_str);
	new_line = ft_strjoin(tmp, after);
	free(before);
	free(after);
	free(status_str);
	free(tmp);
	return (new_line);
}
char	*ft_expand_line(char *line, t_cli *cli)
{
	int		i;
	char	*t;

	i = 0;
	while (line && i < ft_strlen(line))
	{
		if (line[i] == '\'' && i > 0 && line[i - 1] != '\\')
			i += (ft_quoted_len(line + i, '\'') + 1);
		if (i < ft_strlen(line) && line[i] == '<' && line[i + 1] == '<')
		{
			if (ft_heredoc_len(line + i) <= 0)
				return (free(line), line = NULL, NULL);
			i += (ft_heredoc_len(line + i) - 1);
		}
		if (i < ft_strlen(line) && line[i] == '$' && line[i + 1] == '?')
		{
			t = ft_expand_exit_status(cli->status, line, i);
			if (line != t)
				free(line);
			line = t;
			i += 1;
			continue;
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

char	**ft_expand_tokens(char **tokens, int *len, t_cli *cli)
{
	char	*t;
	int		i;

	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		t = ft_expand_line(tokens[i], cli);
		if (t && t[0] == '<' && t[1] == '<')
			tokens[i] = ft_strdup(t);
		else
			tokens[i] = ft_escape_quotes(t);
		free(t);
		i++;
	}
	return (tokens);
}