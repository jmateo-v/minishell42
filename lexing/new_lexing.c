/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:58:52 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/10/06 16:57:19 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
        // Detect shell operators like >, >>, <, <<, |
        if (state == QUOTE_NONE && (c == '>' || c == '<' || c == '|')) {
    // Flush any buffered segments into a token
    if (seg_i > 0) {
        tokens[token_i].segments = calloc(seg_i + 1, sizeof(t_segment));
        memcpy(tokens[token_i].segments, segments, sizeof(t_segment) * seg_i);
        token_i++;
        seg_i = 0;
    }

    // Handle >> or <<
    buffer[0] = c;
    if ((c == '>' || c == '<') && line[i + 1] == c) {
        buffer[1] = c;
        buffer[2] = '\0';
        i++;
    } else {
        buffer[1] = '\0';
    }

    // Create a new token for the operator
    tokens[token_i].segments = calloc(2, sizeof(t_segment));
    tokens[token_i].segments[0].value = strdup(buffer);
    tokens[token_i].segments[0].type = OPERATOR;
    token_i++;
    continue;
}

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

