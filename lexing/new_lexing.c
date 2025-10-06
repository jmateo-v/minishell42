/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:58:52 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/10/06 12:17:11 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_segments(t_token *tok)
{
    if (!tok || !tok->segments) {
        printf("[no segments]\n");
        return;
    }

    for (size_t i = 0; tok->segments[i].value; i++) {
        const char *type_str = NULL;
        switch (tok->segments[i].type) {
            case QUOTE_NONE:   type_str = "NONE";   break;
            case QUOTE_SINGLE: type_str = "SINGLE"; break;
            case QUOTE_DOUBLE: type_str = "DOUBLE"; break;
            default:           type_str = "???";    break;
        }
        printf("SEG[%zu]: type=%s, value=\"%s\"\n",
               i, type_str, tok->segments[i].value);
    }
}

t_token *ft_token_sep(char *line) {
    t_quote_type state = QUOTE_NONE;
    char buffer[1024];
    int buf_i = 0;
    int token_i = 0;
    t_token *tokens = calloc(64, sizeof(t_token));
    t_segment *segments = calloc(64, sizeof(t_segment));
    int seg_i = 0;

    if (!line || !tokens || !segments)
        return NULL;

    for (int i = 0; line[i]; i++) 
    {
        char c = line[i];
        if (c == '$' && line[i + 1] && line[i + 1] == '"' && line[i + 2]) 
        {
        // Flush the current buffer as a normal segment
        if (buf_i > 0) 
        {
            buffer[buf_i] = '\0';
            segments[seg_i].value = strdup(buffer);
            segments[seg_i].type = QUOTE_NONE;
            seg_i++;
            buf_i = 0;
        }

        i += 2; // Skip over $" 

        // Start collecting translation string
        while (line[i] && line[i] != '"') 
        {
            if (buf_i < (int)sizeof(buffer) - 1)
                buffer[buf_i++] = line[i++];
        }

        if (line[i] != '"') 
        {
            fprintf(stderr, "minishell: syntax error near unexpected token `\"'\n");
            free(segments);
            ft_free_tokens(tokens);
            return NULL;
        }
        

        buffer[buf_i] = '\0';
        segments[seg_i].value = strdup(buffer);
        segments[seg_i].type = QUOTE_TRANSLATION;
        seg_i++;
        buf_i = 0;
        continue;
        }
        
        if (state == QUOTE_NONE) {
            if (c == '\'') {
                if (buf_i > 0) {
                    buffer[buf_i] = '\0';
                    segments[seg_i].value = strdup(buffer);
                    segments[seg_i].type = QUOTE_NONE;
                    seg_i++;
                    buf_i = 0;
                }
                state = QUOTE_SINGLE;
            } else if (c == '"') {
                if (buf_i > 0) {
                    buffer[buf_i] = '\0';
                    segments[seg_i].value = strdup(buffer);
                    segments[seg_i].type = QUOTE_NONE;
                    seg_i++;
                    buf_i = 0;
                }
                state = QUOTE_DOUBLE;
            } else if (isspace((unsigned char)c)) {
                if (buf_i > 0) {
                    buffer[buf_i] = '\0';
                    segments[seg_i].value = strdup(buffer);
                    segments[seg_i].type = QUOTE_NONE;
                    seg_i++;
                    buf_i = 0;
                }
                if (seg_i > 0) {
                    tokens[token_i].segments = calloc(seg_i + 1, sizeof(t_segment));
                    memcpy(tokens[token_i].segments, segments, sizeof(t_segment) * seg_i);
                    token_i++;
                    seg_i = 0;
                }
            } else {
                if (buf_i < (int)sizeof(buffer) - 1)
                    buffer[buf_i++] = c;
            }
        } else if (state == QUOTE_SINGLE) {
            if (c == '\'') {
                buffer[buf_i] = '\0';
                segments[seg_i].value = strdup(buffer);
                segments[seg_i].type = QUOTE_SINGLE;
                seg_i++;
                buf_i = 0;
                state = QUOTE_NONE;
            } else {
                if (buf_i < (int)sizeof(buffer) - 1)
                    buffer[buf_i++] = c;
            }
        } else if (state == QUOTE_DOUBLE) {
            if (c == '"') {
                buffer[buf_i] = '\0';
                segments[seg_i].value = strdup(buffer);
                segments[seg_i].type = QUOTE_DOUBLE;
                seg_i++;
                buf_i = 0;
                state = QUOTE_NONE;
            } else {
                if (buf_i < (int)sizeof(buffer) - 1)
                    buffer[buf_i++] = c;
            }
        }
    }

    if (buf_i > 0) {
        buffer[buf_i] = '\0';
        segments[seg_i].value = strdup(buffer);
        segments[seg_i].type = QUOTE_NONE;
        seg_i++;
        buf_i = 0;
    }

    if (seg_i > 0) {
        tokens[token_i].segments = calloc(seg_i + 1, sizeof(t_segment));
        memcpy(tokens[token_i].segments, segments, sizeof(t_segment) * seg_i);
        token_i++;
    }

    tokens[token_i].segments = NULL;
    tokens[token_i].value = NULL;

    if (state != QUOTE_NONE) {
        fprintf(stderr, "minishell: syntax error near unexpected token %c'\n",
                state == QUOTE_SINGLE ? '\'' : '"');
        free(segments);
        ft_free_tokens(tokens);
        return NULL;
    }

    free(segments);
    free(line);
    return tokens;
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
