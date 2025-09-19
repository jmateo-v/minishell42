/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:55 by rafael-m          #+#    #+#             */
/*   Updated: 2025/09/19 12:45:05 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_redirs(char **token, int i)
{
	char	*s;

	if (token[i] && ft_strchr(REDIR_S, token[i][0]) && (!token[i][1] || (token[i][1] == token[i][0] && !token[i][2])))
	{
		printf("token[i + 1] = %s\n", token[i + 1]);
		if (!token[i + 1])
			return (ft_perror("newline", SYN_ERR), 1);
		s = ft_strndup(token[i], 3);
		printf("s = %s\n", s);
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
		return (ft_perror(token[0], SYN_ERR), 1);
	i = 0;
	while (i < len)
	{
		if (token[i] && ft_strchr(OP_STR2, token[i][0]) && (token[i + 1] && ft_strchr(OP_STR2, token[i + 1][0])))
			return (ft_perror(token[i + 1], SYN_ERR), 1);
		else if (token[i] && token[i][0] == ')' && (token[i + 1] && !ft_strchr(OP_STR, token[i + 1][0])))
			return (ft_perror(token[i + 1], SYN_ERR), 1);
		else if (token[i] && token[i][0] == '(' && i > 0 && (!ft_strchr(OP_STR, token[i - 1][0])))
			return (ft_perror(token[i + 1], SYN_ERR), 1);
		else if (token[i] && token[i][0] == '(' && token[i + 1] && token[i + 1][0] == ')')
			return (ft_perror(token[i + 1], SYN_ERR), 1);
		else if (token[i] && ft_strchr(OP_STR, token[i][0]) && ! token[i + 1])
			return (ft_perror(token[i], SYN_ERR), 1);
		else if (token[i] && ft_check_redirs(token, i))
			return (1);
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
	if (ft_isspace(line[pos]) || (ft_strchr(REDIR_S, line[pos])))
		return (pos);
	if (pos == 0 && ft_strchr(OP_STR2, line[pos]) && line[pos + 1] == line[pos])
		return (2);
	if (pos == 0 && ft_strchr(OP_STR, line[pos]))
		return (1);
}

int	ft_token_len(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	while (i < len && ft_isspace(line[i]))
		i++;
	if (i < len && ft_strchr(REDIR_S, line[i]))
		return (ft_heredoc_len(line + i));
	while (i < len)
	{
		if (ft_strchr(QUOTES, line[i]) && (i == 0 || (i > 0 && line[i - 1] != '\\')))
		{
			if (ft_quoted_len(line + i, line[i]) <= 0)
				return (-1);
			i = (ft_quoted_len(line + i, line[i]) + i);
			continue ;
		}
		if (ft_strchr(SEP_STR, line[i]) && i != 0)
			return (i);
		if (ft_strchr(SEP_STR, line[i]) && i == 0)
			return (ft_sep_len(line + i, i));	
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

char	**ft_token_sep(char *line)
{
	int		i;
	int		j;
	int		len;
	char	**tokens;

	if (!line)
		return (NULL);
	len = ft_num_s_tokens(line);
	if (len <= 0)
		return (free(line), NULL);
	tokens = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!tokens)
		return (free(line), perror("minishell: malloc : "), NULL);
	i = 0;
	j = 0;
	while (tokens && i < ft_strlen(line))
	{
		while (ft_isspace(line[i]))
			i++;
		if (ft_token_len(line + i) <= 0)
			return (tokens[j] = NULL, ft_free_d(tokens), free(line), NULL);
		tokens[j] = ft_strndup(line + i, ft_token_len(line + i));
		if (!tokens[j])
		{
			tokens[j] = NULL;
			ft_free_d(tokens);
			free(line);
			return (NULL);
		}
		j++;
		i += ft_token_len(line + i);
	}
	return (free(line), tokens[len] = NULL, tokens);
}
