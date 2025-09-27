/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:58:52 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/09/27 11:39:57 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_tokens_on_error(t_token *tokens, int count)
{
    int i;

    i = 0;
    if (!tokens)
        return ;
    while (i < count)
    {
        free(tokens[i].value);
        tokens[i].value = NULL;
        i++;
    }
    free (tokens);
}


t_token	*ft_token_sep(char *line)
{
	int		i;
	int		j;
	int		len;
	int		start;
	int		token_count;
	t_token	*tokens;

	i = 0;
	j = 0;
	token_count = ft_count_tokens(line);
	if (token_count <= 0 || !line)
		return (free(line), NULL);
	
	tokens = (t_token *)ft_calloc(token_count + 1, sizeof(t_token));
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
				return (free(line), ft_free_tokens_on_error(tokens, j), NULL);
            if (len == 2) // just "" or ''
                tokens[j].value = ft_strdup(""); // not ft_strndup
            else
                tokens[j].value = ft_strndup(&line[i], len);
			tokens[j].quoted = true;
			i += len;
			j++;
			continue;
		}
		else
        {
            start = i;
            while (line[i] && !ft_isspace(line[i]) && !ft_strchr(QUOTES, line[i]))
                i++;

            len = i - start;
            tokens[j].value = ft_strndup(&line[start], len);
            tokens[j].quoted = false;
            j++;
        }
    }
	tokens[j].value = NULL;
	free(line);
	return (tokens);
}

t_token *ft_strip_quotes(t_token *tokens)
{
	int i;
	char *escaped;

	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens[i].value)
	{

		escaped = ft_escape_quotes(tokens[i].value);
		if (!escaped)
			return (ft_free_tokens(tokens), NULL);
		free(tokens[i].value);
		tokens[i].value = escaped;

		i++;
	}
	return (tokens);
}
