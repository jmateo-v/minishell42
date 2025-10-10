/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:55 by rafael-m          #+#    #+#             */
/*   Updated: 2025/10/10 16:32:24 by dogs             ###   ########.fr       */
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

int ft_check_errors(t_token *tokens, int len)
{
    int i = 0;
    int has_command = 0;

    while (i < len)
    {
        has_command = 0;

        while (i < len && !(tokens[i].value[0] == '|' && tokens[i].value[1] == '\0'))
        {
            char *curr = tokens[i].value;
            char *next = (i + 1 < len) ? tokens[i + 1].value : NULL;

            if (!curr || curr[0] == '\0') {
                i++;
                continue;
            }

            if (ft_strchr("<>", curr[0])) {
                if (!next || ft_strchr("|&", next[0]))
                    return (ft_perror(curr, SYN_ERR), 1);
            }

            if (!ft_strchr("|&<>", curr[0]))
                has_command = 1;

            i++;
        }

        if (!has_command)
            return (ft_perror(tokens[i].value, SYN_ERR), 1);

        i++;
    }

    return 0;
}





int	ft_sep_len(char *line, int pos)
{
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
	while (i < len && ft_isspace(line[i]))
		i++;
	if (ft_strchr(SEP_STR, line[i]))
		return (i + ft_sep_len(line, i));
	
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
int ft_token_count(t_token *tokens)
{
    int count = 0;

    if (!tokens)
        return 0;

    while (tokens[count].segments)
    {
        if (tokens[count].value != NULL)
            count++;
        else
            break;
    }
    return count;
}




