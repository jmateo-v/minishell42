/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:19:54 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/31 17:35:39 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_list(t_cli *cli)
{
	int	i = 0;
	int	node = 0;

	if (!cli)
		return ;
	while (cli)
	{
		if (!cli)
			return ;
		if (cli->cmd)
			printf("cmd %d = %s\n", node, cli->cmd);
		if (cli->infile)
			printf("infile %d = %s\n", node, cli->infile);
		if (cli->outfile)
			printf("outfile %d = %s\n", node, cli->outfile);
		if (cli->is_builtin)
			printf("is_builtin %d = %d\n", node, cli->is_builtin);
		if (cli->r_mode)
			printf("r_mode %d = %d\n", node, cli->r_mode);
		if (cli->heredoc)
			printf("heredoc %d = %s\n", node, cli->heredoc);
		printf("op = %d\n", cli->op);
		printf("priority = %d\n", cli->priority);
		while (cli->args && i < ft_doubleptr_len((void **)cli->args))
		{
			printf("args[%d] %d = %s\n", i, node, cli->args[i]);
			i++;
		}
		i = 0;
		// while (cli->env && cli->env[i])
		// {
		// 	printf("env[%d] %d = %s\n", i, node, cli->env[i]);
		// 	i++;
		// }
		cli = cli->next;
		node++;
	}
}

void	ft_perror(char *token, char *msg)
{
	char	*t;
	char	*err;

	t = ft_strjoin(msg, token);
	err = ft_strjoin(t, "'\n");
	write(2, err, ft_strlen(t));
	free(t);
	free(err);
}

void	ft_free_tokens(char **tokens, int n)
{
	int	i;

	i = 0;
	while (tokens && i <= n)
	{
		free(tokens[i]);
		i++;
	}
	if (tokens)
		free(tokens);
}

t_cli	*ft_init_node(int len, char **env, int op)
{
	t_cli *cli;

	if (len <= 0)
		return (NULL);
	cli = (t_cli *)ft_calloc(1, sizeof(t_cli));
	if (!cli)
		return (ft_free_d(env), perror("malloc : "), NULL);
	cli->cmd = NULL;
	cli->args = NULL;
	cli->env = ft_load_env(env);
	if (env && !cli->env)
		perror("malloc : ");
	cli->infile = NULL;
	cli->outfile = NULL;
	cli->heredoc = NULL;
	cli->heredoc_fd = -1;
	cli->is_builtin = 0;
	cli->next = NULL;
	cli->r_mode = WRITE;
	cli->n_tokens = len;
	cli->priority = 1;
	cli->op = op;
	return (cli);
}

void	ft_free_list(t_cli **cli)
{
	t_cli		*node;
	t_cli		*next_node;

	if (!cli || !*cli)
		return ;
	node = *cli;
	while (node)
	{
		next_node = node->next;
		free(node->cmd);
		node->cmd = NULL;
		free(node->heredoc);
		node->heredoc = NULL;
		free(node->infile);
		node->infile = NULL;
		free(node->outfile);
		node->outfile = NULL;
		ft_free_d(node->env);
		node->env = NULL;
		ft_free_d(node->args);
		node->args = NULL;
		free(node);
		node = next_node;
	}
	*cli = NULL;
	return ;
}

int ft_trim_s_len(char *line)
{
	int		i;
	int		len;
	char	sep;

	i = 0;
	len = 0;
	sep = '\0';
	while (line && ft_isspace(line[i]))
		i++;
	while (line && i < ft_strlen(line))
	{
		if (ft_strchr(QUOTES, line[i]))
		{
			sep = line[i];
			if (ft_quoted_len(line + i, sep)  <= 0)
				return (-1);
			len += ft_quoted_len(line + i, sep);
			i += ft_quoted_len(line + i, sep);
			sep = '\0';
			continue ;
		}
		while (ft_isspace(line[i]) && (( i + 1) >= ft_strlen(line) || ft_isspace(line[i + 1])))
			i++;
		i++;
		len++;
	}
	return (len);
}

char	*ft_trim_spaces(char *line)
{
	int		i;
	int		j;
	char	sep;
	char	*trimmed;

	i = 0;
	j = 0;
	trimmed = ft_calloc(ft_trim_s_len(line) + 1, sizeof(char));
	while (line && ft_isspace(line[i]))
		i++;
	while (trimmed && line && i < ft_strlen(line))
	{
		while (ft_isspace(line[i]) && (ft_isspace(line[i + 1]) || !line[i + 1]))
			i++;
		if (i < ft_strlen(line) && ft_strchr(QUOTES, line[i]))
		{
			sep = line[i];
			trimmed[j++] = line[i++];
			while (i < ft_strlen(line) && line[i] != sep)
				trimmed[j++] = line[i++];
		}
		if (i < ft_strlen(line))
			trimmed[j++] = line[i++];
	}
	return (trimmed);
}
