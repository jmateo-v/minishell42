/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:24 by rafael-m          #+#    #+#             */
/*   Updated: 2025/10/06 12:30:14 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_split(char **arr)
{
    int i;

    if (!arr)
        return;
    for (i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}

char	*ft_trim_delim(char *token, int *option)
{
	char	*delim;
	int		i;

	if (!token)
		return (NULL);
	i = 0;
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

char	*ft_expand_exit_status(int status, char *line, int i)
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

/*char	*ft_expand_var(char	*line, int start, int end)
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
}/*/
char *ft_expand_var(const char *var, t_shenv *env, t_cli *cli)
{
    if (!var || !*var)
        return strdup("");

    if (strcmp(var, "?") == 0) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", cli ? cli->last_status : 0);
        return strdup(buf);
    }

    if (!env)
        return strdup("");

    for (t_shenv *cur = env; cur; cur = cur->next) {
        if (!cur->var)
            continue;
        char *eq = strchr(cur->var, '=');
        if (!eq)
            continue;
        size_t name_len = eq - cur->var;
        size_t var_len = strlen(var);
        if (name_len == var_len && strncmp(cur->var, var, var_len) == 0) {
            return strdup(eq + 1);
        }
    }

    return strdup("");
}


void insert_token(t_token **tokens, int *len, int pos, const char *value)
{
    // grow the array by 1
    t_token *new_tokens = realloc(*tokens, sizeof(t_token) * (*len + 2));
    if (!new_tokens)
        return; // handle error properly in your project

    *tokens = new_tokens;

    // shift tokens after pos to the right
    for (int i = *len; i > pos; i--) {
        (*tokens)[i] = (*tokens)[i - 1];
    }

    // insert new token
    (*tokens)[pos].value = ft_strdup(value);
    (*tokens)[pos].quote_type = QUOTE_NONE;

    (*len)++;
    // null‑terminate if you rely on that
    (*tokens)[*len].value = NULL;
}

char	*ft_expand_line(char *line, t_cli *cli)
{
    
	size_t		i;
	char	*t;

    (void)cli;
	if (!line)
		return (NULL);
	i = 0;
	while (line && i < ft_strlen(line))
	{
		if (line[i] == '\'' && (i == 0 || line[i - 1] != '\\'))
		{
			i += (ft_quoted_len(line + i, '\'') + 1);
			continue;
		}
		if (i < ft_strlen(line) && line[i] == '<' && line[i + 1] == '<')
		{
			if (ft_heredoc_len(line + i) <= 0)
				return (free(line), line = NULL, NULL);
			i += (ft_heredoc_len(line + i) - 1);
			continue;
		}
		i++;
	}
	t = ft_strtrim(line, " ");
	return (free(line), t);
}
static void cleanup(char *a, char *b, char *c, char *d)
{
    free(a);
    free(b);
    free(c);
    free(d);
}
t_token *ft_expand_tokens(t_token *tokens, int *len, t_cli *cli)
{
    if (!tokens || !len || *len <= 0 || !cli)
        return NULL;

    for (int i = 0; i < *len; i++) {
        char *result = strdup("");
        if (!result)
            return NULL;

        if (!tokens[i].segments) {
            if (tokens[i].value)
                free(tokens[i].value);
            tokens[i].value = result;
            continue;
        }

        for (int s = 0; tokens[i].segments[s].value; s++) {
            t_segment *seg = &tokens[i].segments[s];
            char *expanded = NULL;
            char *seg_expanded = NULL;
            char *val = NULL;

            if (!seg->value) {
                expanded = strdup("");
            } 
            else if (seg->type == QUOTE_SINGLE) 
            {
                expanded = strdup(seg->value);
            }
            else if (seg->type == QUOTE_TRANSLATION)
            {
                expanded = strdup(seg->value);
            }
             else {
                seg_expanded = strdup("");
                
                if (!seg_expanded) 
                {
                    cleanup(result, expanded, seg_expanded, val);
                    return NULL;
                }
                for (int j = 0; seg->value[j]; j++)
                {
                    if (seg->value[j] == '$')
                    {
                        char next = seg->value[j + 1];

                    // If there's no valid variable character after $, treat it as literal $
                        if (!next || !(isalnum((unsigned char)next) || next == '_' || next == '?')) 
                        {
                            char *tmp2 = ft_strjoin(seg_expanded, "$");
                            free(seg_expanded);
                            seg_expanded = tmp2;

                            if (!seg_expanded) 
                            {
                                cleanup(result, expanded, seg_expanded, val);
                                return NULL;
                            }
                            continue;
                        }

                        j++; // Move past $

                        char var[128] = {0};
                        int vi = 0;

                        if (seg->value[j] == '?') 
                        {
                            var[vi++] = '?';
                            j++;
                        } 
                        else 
                        {
                            while (seg->value[j] && (isalnum((unsigned char)seg->value[j]) || seg->value[j] == '_')) 
                            {
                                if (vi < (int)sizeof(var) - 1)
                                    var[vi++] = seg->value[j++];
                                else
                                    j++;
                            }
                        }

                        j--; // Step back so outer loop doesn't skip a character

                        val = ft_expand_var(var, *cli->env, cli);
                        if (!val)
                        val = strdup("");

                        char *tmp2 = ft_strjoin(seg_expanded, val);
                        free(seg_expanded);
                        free(val);
                        seg_expanded = tmp2;

                        if (!seg_expanded) 
                        {
                            cleanup(result, expanded, seg_expanded, NULL);
                            return NULL;
                        }
                    } 
                    else 
                    {
                        char one[2] = { seg->value[j], '\0' };
                        char *tmp2 = ft_strjoin(seg_expanded, one);
                        free(seg_expanded);
                        seg_expanded = tmp2;

                        if (!seg_expanded)
                        {
                            cleanup(result, expanded, seg_expanded, val);
                            return NULL;
                        }
                    }
                }

                expanded = seg_expanded;
            }

            char *tmp = ft_strjoin(result, expanded);
            if (!tmp) {
                cleanup(result, expanded, seg_expanded, val);
                return NULL;
            }
            free(result);
            free(expanded);
            expanded = NULL;
            result = tmp;

            if (!result) {
                cleanup(result, expanded, seg_expanded, val);
                return NULL;
            }
        }

        if (tokens[i].value)
            free(tokens[i].value);

        tokens[i].value = result;
    }

    return tokens;
}




