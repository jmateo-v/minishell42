/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:58:52 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/10/11 16:52:30 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_token_finalize(t_token *tok)
{
    int   total_len = 0;
    int   i = 0;
    char *res;

    if (!tok || !tok->segments || !tok->segments[0].value)
        return (0);

    while (tok->segments[i].value)
    {
        total_len += (int)strlen(tok->segments[i].value);
        i++;
    }

    res = malloc(total_len + 1);
    if (!res)
        return (0);

    res[0] = '\0';
    i = 0;
    while (tok->segments[i].value)
    {
        strcat(res, tok->segments[i].value);
        i++;
    }

    tok->value = res;

    tok->quote_type = tok->segments[0].type;

    return (1);
}

void ft_finalize_tokens(t_token *tokens)
{
    int i = 0;

    while (tokens[i].segments)
    {
        if (!tokens[i].value)
            ft_token_finalize(&tokens[i]);
        i++;
    }
}


t_token *ft_token_sep(char *line) {
    t_quote_type state = QUOTE_NONE;
    //probably should improve this one :)
    int len = ft_strlen(line);
    char buffer[1024];
    int buf_i = 0;
    int token_i = 0;
    t_token *tokens = ft_calloc(len + 1, sizeof(t_token));
    t_segment *segments = ft_calloc(len + 1, sizeof(t_segment));
    int seg_i = 0;

    if (!line || !tokens || !segments)
        return NULL;

    for (int i = 0; line[i]; i++) 
    {
        char c = line[i];
        if (state == QUOTE_NONE && (c == '>' || c == '<' || c == '|')) {
    if (seg_i > 0) {
        tokens[token_i].segments = calloc(seg_i + 1, sizeof(t_segment));
        memcpy(tokens[token_i].segments, segments, sizeof(t_segment) * seg_i);
        token_i++;
        seg_i = 0;
    }

    buffer[0] = c;
    if ((c == '>' || c == '<') && line[i + 1] == c) {
        buffer[1] = c;
        buffer[2] = '\0';
        i++;
    } else {
        buffer[1] = '\0';
    }

    tokens[token_i].segments = calloc(2, sizeof(t_segment));
    tokens[token_i].segments[0].value = strdup(buffer);
    tokens[token_i].segments[0].type = OPERATOR;
    token_i++;
    continue;
}

        if (c == '$' && line[i + 1] && line[i + 1] == '"' && line[i + 2]) 
        {
        if (buf_i > 0) 
        {
            buffer[buf_i] = '\0';
            segments[seg_i].value = strdup(buffer);
            segments[seg_i].type = QUOTE_NONE;
            seg_i++;
            buf_i = 0;
        }

        i += 2;

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

