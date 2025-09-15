/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:19:16 by rafael-m          #+#    #+#             */
/*   Updated: 2025/09/15 16:17:44 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_rec = 0;

// char	*get_pwd(char *cwd)
// {
// 	char	*home;
// 	char	*pwd;
// 	char	*t;

// 	if (!cwd)
// 		return (NULL);
// 	home = ft_strtrim(getenv("HOME"), "HOME=");
// 	if (!home)
// 		return (NULL);
// 	if (!ft_strncmp(home, cwd, ft_strlen(home)))
// 	{
// 		t = ft_strtrim(cwd, home);
// 		pwd = ft_strjoin("~/", t);
// 		return (free(home), free(t), pwd);
// 	}
// 	pwd = ft_strdup(cwd);
// 	return (free(home), pwd);
// }

// char	*get_hostname(void)
// {
// 	char	*r;
// 	char	*buffer;
// 	char	*t;
// 	int		fd;

// 	r = NULL;
// 	fd = open("/etc/hostname", O_RDONLY);
// 	buffer = ft_calloc(2, sizeof(char));
// 	if (fd == -1 || ! buffer)
// 		return (free(buffer), NULL);
// 	read(fd, buffer, 1);
// 	while (buffer[0] != '\n' && buffer[0] != EOF)
// 	{
// 		t = r;
// 		r = ft_strjoin(r, buffer);
// 		read(fd, buffer, 1);
// 		free(t);
// 	}
// 	return (free(buffer), close(fd), r);
// }

// char	*ft_prompt(char **envp)
// {
// 	char	*user;
// 	char	*pwd;
// 	char	*prompt;
// 	char	*t;

// 	if (!envp)
// 		return (NULL);
// 	user = ft_strtrim(getenv("USER"), "USER=");
// 	t = (char *)ft_calloc(4096, sizeof(char));
// 	if (!t || ! user)
// 		return (perror("malloc: "), NULL);
// 	pwd = get_pwd(getcwd(t, 4096));
// 	free(t);
// 	prompt = ft_strjoin(user, "@");
// 	free(user);
// 	user = get_hostname();
// 	t = ft_strjoin(prompt, user);
// 	free(user);
// 	free(prompt);
// 	prompt = ft_strjoin(t, ":");
// 	free(t);
// 	t = ft_strjoin(prompt, pwd);
// 	free(prompt);
// 	prompt = ft_strjoin(t, "$ ");
// 	return (free(t), free(pwd), prompt);
// }
// char	*ft_here_prnts(char *line)
// {
// 	char	*new_line;
// 	char	*t;
// 	int		i;
// 	int	end;

// 	if (!line)
// 		return (NULL);
// 	new_line = NULL;
// 	end = 0;
// 	while (1)
// 	{
// 		i = 0;
// 		free(new_line);
// 		new_line = readline("> ");
// 		if (g_sig_rec)
// 			return (free(new_line), g_sig_rec = 0, line);
// 		if (!new_line)
// 			return (free(line), line = NULL, write(2, UNEX_EOF, 49), NULL);
// 		while (new_line && ft_isspace(new_line[i]))
// 			i++;
// 		if (!new_line[i] || new_line[i] == '\n')
// 			continue ;
// 		if (ft_strchr(new_line, ')'))
// 			end = 1;
// 		t = ft_strjoin(line, new_line);
// 		free(line);
// 		line = t;
// 		if (end)
// 			break ;
// 	}
// 	return (free(new_line), line);
// }

int	ft_check_prnts(char *line)
{
	int		i;
	int		len;
	int		prnts;

	if (!line)
		return (-1);
	i = 0;
	prnts = 0;
	while (i < ft_strlen(line))
	{
		if (ft_strchr(QUOTES, line[i]) && (i == 0 || (i > 0 && line[i - 1] != '\\')))
		{
			len = ft_quoted_len(line + i, line[i]);
			if (len < 0)
			{
				write(2, ERR_OPEN_Q, 43);
				return (-1);
			}
			i += (len - 1);
		}
		if (line[i] == '(')
			prnts++;
		if (line[i] == ')')
			prnts--;
		i++;
	}
	if (prnts)
		write(2, "minishell : extra parenthesis\n", 30);
	return (prnts);
}

void	ft_reset_list(t_cli *cli)
{
	t_cli	*next;
	t_cli	*node;

	node = cli;
	while (node->next)
		node = node->next;
	cli->status = node->status;
	next = cli->next;
	ft_free_list(&next);
	cli->next = NULL;
	free(cli->cmd);
	cli->cmd = NULL;
	free(cli->heredoc);
	cli->heredoc = NULL;
	free(cli->infile);
	cli->infile = NULL;
	free(cli->outfile);
	cli->outfile = NULL;
	ft_free_tokens(cli->args, cli->n_tokens - 1);
	cli->args = NULL;
	cli->is_builtin = 0;
	cli->r_mode = 0;
	cli->group = 0;
	cli->op = 0;
}

int	ft_reset_signal(t_cli *cli)
{
	g_sig_rec = 0;
	ft_reset_list(cli);
	cli->status = 130;
	return (1);
}

int	ft_read_line(t_shenv *env, t_cli *cli)
{
	char	*cl;
	char	**tokens;

	cl = NULL;
	while (1)
	{
		free(cl);
		printf("status = %d\n", cli->status);
		cl = readline("\033[1;32mminishell\033[0m$ ");
		if (!cl)
			return (rl_clear_history(), write(1, "exit\n", 5), 0);
		if (g_sig_rec && ft_reset_signal(cli))
			continue ;
		add_history(cl);
		tokens = ft_tokens(cl, env, cli);
		if (!tokens)
		{
			cli->status = 2;
			continue ;
		}
		cli->status = ft_parse(tokens, cli);
		cli->status = ft_execute(cli);
		//ft_print_list(cli);
		ft_reset_list(cli);
	}
	return (free(cl), rl_clear_history(), cli->status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shenv		*env;
	extern int 	rl_catch_signals;
	t_cli		*cli;
	int			status;
	
	ft_set_sig(PARENT);
	rl_catch_signals = 0;
	env = ft_load_env(envp);
	cli = ft_init_node(1, env, 0);
	
	if (!cli)
		return (ft_free_env(&env), 2);
	status = ft_read_line(env, cli);
	
	ft_free_list(&cli);
	ft_free_env(&env);
	return (status);
}