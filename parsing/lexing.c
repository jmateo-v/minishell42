/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:18:45 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/27 16:48:32 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_quoted_len(char *line, char quote)
{
	int	i;

	if (!line)
		return (0);
	i = 1;
	while (line[i])
	{
		if (line[i] == quote)
			return (i + 1);
		i++;
	}
	write(2, ERR_OPEN_Q, 43);
	return (-1);
}

char	*ft_escaped_line(char *line, int start, int end)
{
	char	*escaped;
	char	*t;
	char	*s;

	if (!line || start < 0 || end < start)
		return (NULL);
	if (end == 0)
		return (ft_strdup(line));
	escaped = ft_esc_str(line + start + 1, ESC_CHARS1, end - start - 2);
	t = ft_strndup(line, start);
	if (!escaped)
		return (NULL);
	s = ft_strjoin(t, escaped);
	if (!s)
		return (NULL);
	free(escaped);
	free(t);
	t = ft_strjoin(s, line + end);
	free(s);
	return (s = NULL, escaped = NULL, t);
}

char	*ft_escape_quotes(char *line)
{
	int		i;
	int		len;
	char	*esc_line;
	char	*s;

	if (!line)
		return (NULL);
	i = 0;
	s = ft_strdup(line);
	while (i < ft_strlen(s))
	{
		if (ft_strchr(QUOTES, s[i]))
		{
			if (s[i + 1] == s[i])
				return (free(s), NULL);
			len = ft_quoted_len(s + i,  s[i]);
			if (len <= 0)
				return (free(s), NULL);
			esc_line = ft_escaped_line(s, i, i + len);
			free(s);
			s = esc_line;
			if (s != esc_line)
				free(esc_line);
			i += (len - 3);
		}
		i++;
	}
	return (s);
}

void	ft_free_all(char **token, t_cli **cli, char **env)
{
	if (token && cli && *cli)
		ft_free_tokens(token, (*cli)->n_tokens);
	else if (token)
		ft_free_d(token);
	if (cli && *cli)
		ft_free_list(cli);
	if (env)
		ft_free_d(env);	
}

t_cli	*ft_tokens(char *line, char **envp)
{
	char	*s;
	char	**tokens;
	char	**env;
	t_cli	*cli;

	if (!line)
		return(NULL);
	s = ft_trim_spaces(line);
	tokens = ft_token_sep(s);
	free(s);
	env = ft_load_env(envp);
	cli = ft_init_node(ft_num_s_tokens(line), env);
	if (!tokens || !cli)
		return (ft_free_all(tokens, &cli, env), NULL);
	tokens = ft_expand_tokens(tokens, &(cli->n_tokens));
	if (!tokens)
		return (ft_free_all(tokens, &cli, env), NULL);
	if (tokens && tokens[0] && tokens[0][0] == '|')
		return (ft_free_all(tokens, &cli, env), write(2, "minishell: syntax error near unexpected token `|'\n", 50), NULL);
	ft_parse(tokens, cli);
	ft_free_tokens(tokens, cli->n_tokens);
	ft_free_d(env);
	return (cli);
}
