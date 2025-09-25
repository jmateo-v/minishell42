/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:55 by rafael-m          #+#    #+#             */
/*   Updated: 2025/09/25 17:46:42 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_redirs(char **token, int i)
{
	char	*s;

	if (token[i] && ft_strchr(REDIR_S, token[i][0]) && (!token[i][1] || (token[i][1] == token[i][0] && !token[i][2])))
	{
		if (!token[i + 1])
			return (ft_perror("newline", SYN_ERR), 1);
		s = ft_strndup(token[i], 3);
		ft_perror(s, SYN_ERR);
		free(s);
		return (1);
	}
	return (0);
}

int	ft_check_errors(char **token, int len)
{
	int	i;

	if (!token)
		return (1);
	if (token[0] && ft_strchr(OP_STR2, token[0][0]))
		return (printf("1\n"), ft_perror(token[0], SYN_ERR), 1);
	i = 0;
	while (i < len)
	{
		// printf("token[%d] = %s\n", i, token[i]);
		if (token[i] && ft_strchr(OP_STR2, token[i][0]) && (token[i + 1] && ft_strchr(OP_STR2, token[i + 1][0])))
			return (printf("2\n"), ft_perror(token[i + 1], SYN_ERR), 1);
		else if (token[i] && token[i][0] == ')' && (token[i + 1] && !ft_strchr(OP_STR, token[i + 1][0])))
			return (printf("3\n"), ft_perror(token[i + 1], SYN_ERR), 1);
		else if (token[i] && token[i][0] == '(' && i > 0 && (!ft_strchr(OP_STR, token[i - 1][0])))
			return (printf("4\n"), ft_perror(token[i + 1], SYN_ERR), 1);
		else if (token[i] && token[i][0] == '(' && token[i + 1] && token[i + 1][0] == ')')
			return (printf("5\n"), ft_perror(token[i + 1], SYN_ERR), 1);
		else if (token[i] && ft_strchr(OP_STR, token[i][0]) && !token[i + 1])
			return (printf("6\n"), ft_perror(token[i], SYN_ERR), 1);
		else if (token[i] && ft_strchr(SEP_STR, token[i][0]) && token[i + 1] && ft_strchr(SEP_STR, token[i + 1][0]))
			return (printf("7\n"), ft_perror(token[i + 1], SYN_ERR), 1);
		i++;
	}
	return (0);
}

int	ft_sep_len(char *line, int pos)
{
	char	*err;
	char	*t;
	int		i;

	if (!line || pos < 0)
		return (-1);
	if (ft_isspace(line[pos]))
		return (0);
	if (ft_strchr(SEP_STR, line[pos]) && line[pos + 1] == line[pos])
		return (2);
	if (ft_strchr(SEP_STR, line[pos]))
		return (1);
	return (1);
}

int	ft_token_len(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	// printf("line = '%s'\n", line);
	while (i < len && ft_isspace(line[i]))
		i++;
	// printf("line2 = '%s'\n", line + i);
	if (ft_strchr(SEP_STR, line[i]))
		return (/*printf("t_len = %d\n", i + ft_sep_len(line, i)), */i + ft_sep_len(line, i));
	// printf("i = %d\n", i);
	while (i < len)
	{
		if (ft_strchr(QUOTES, line[i]) && (i == 0 || (i > 0 && line[i - 1] != '\\')))
		{
			if (ft_quoted_len(line + i, line[i]) <= 0)
				return (-1);
			i = (ft_quoted_len(line + i, line[i]) + i);
			continue ;
		}
		if (ft_strchr(SEP_STR, line[i]))
			return (/*printf("t_len2 = %d\n", i), */i);			
		i++;
	}
	return (i);
}

int	ft_num_s_tokens(char *line)
{
	int	i;
	int	len;
	int	line_len;
	int	num_token;

	if (!line)
		return (0);
	i = 0;
	num_token = 0;
	line_len = ft_strlen(line);
	while (i < line_len)
	{
		if (ft_isspace(line[i]) && (ft_isspace(line[i + 1]) || !line[i + 1]))
		{
			i++;
			continue ;
		}
		len = ft_token_len(line + i);
		if (len <= 0)
			return (-1);
		i += len;
		num_token++;
	}
	return (num_token);
}
int	ft_count_tokens(const char *line)
{
	int i;
	int count;
	int len;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break;
		if (ft_strchr(QUOTES, line[i]))
		{
			len = ft_quoted_len((char *)&line[i], line[i]);
			if (len < 0)
				return (-1);
			i += len;
		}
		else
		{
			while (line[i] && !ft_isspace(line[i]) && !ft_strchr(QUOTES, line[i]))
				i++;
		}
		count++;
	}
	return (count);
}
char	**ft_token_sep(char *line)
{
	int		i;
	int		j;
	int		len;
	int		start;
	int		token_count;
	char	**tokens;

	i = 0;
	j = 0;
	token_count = ft_count_tokens(line);
	printf("ft_count_tokens(\"%s\") = %d\n", line, token_count);

	if (token_count <= 0 || !line)
		return (free(line), NULL);
	tokens = (char **)ft_calloc(token_count + 1, sizeof(char *));
	if (!tokens)
		return (free(line), perror("minishell: malloc : "), NULL);
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break;
		if (ft_strchr(QUOTES, line[i]))
		{
			len = ft_quoted_len(&line[i], line[i]);
			if (len < 0)
				return (free(line), ft_free_d(tokens), NULL);
			if (len == 2)
				tokens[j++] = strdup("");
			else
				tokens[j++] = ft_strndup(&line[i + 1], len -2);
			i += len;
		}
		else
		{
			start = i;
			while (line[i] && !ft_isspace(line[i]) && !ft_strchr(QUOTES, line[i]))
				i++;
			len = i - start;
			tokens[j++] = ft_strndup(&line[start], len);
		}
	}
	tokens[j] = NULL;
	free(line);
	return (tokens);
}
