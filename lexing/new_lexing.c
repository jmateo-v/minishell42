/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:58:52 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/09/26 18:00:59 by jmateo-v         ###   ########.fr       */
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
			while (ft_isspace(line[i]))
    			i++;
			j++;
			if (!line[i])
				break;
			
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
