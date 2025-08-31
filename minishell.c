/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:19:16 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/31 17:25:23 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

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
char	*ft_here_prnts(char *line)
{
	char	*new_line;
	char	*t;
	int		i;
	int	end;

	if (!line)
		return (NULL);
	new_line = NULL;
	end = 0;
	while (1)
	{
		i = 0;
		free(new_line);
		new_line = readline("> ");
		if (g_sigint_received)
			return (free(new_line), g_sigint_received = 0, line);
		if (!new_line)
			return (free(line), line = NULL, write(2, UNEX_EOF, 49), NULL);
		while (new_line && ft_isspace(new_line[i]))
			i++;
		if (!new_line[i] || new_line[i] == '\n')
			continue ;
		if (ft_strchr(new_line, ')'))
			end = 1;
		t = ft_strjoin(line, new_line);
		free(line);
		line = t;
		if (end)
			break ;
	}
	return (free(new_line), line);
}

char	*ft_check_prnts(char *line)
{
	int		i;
	int		len;
	int		prnts;

	if (!line)
		return (NULL);
	i = 0;
	prnts = 0;
	while (i < ft_strlen(line))
	{
		if (ft_strchr(QUOTES, line[i]))
		{
			len = ft_quoted_len(line + i, line[i]);
			if (len < 0)
				return (free(line), NULL);
			i += len;	
		}
		if (line[i] == '(')
			prnts = 1;
		if (prnts && line[i] == ')')
			prnts = 0;
		i++;
	}
	if (prnts)
		line = ft_here_prnts(line);
	return (line);
}


int	ft_exec_shell(char **envp)
{
	char	*cl;
	char	**tokens;
	t_cli	*cli;
	int status;
	char *expanded_input;

	cl = NULL;
	tokens = NULL;
	status = 0;
	while (1)
	{
		free(cl);
		cl = readline("\033[1;32mminishell\033[0m$ ");
		if (!cl)
			return (rl_clear_history(), write(1, "exit\n", 5), 0);
		if (ft_strlen(cl) <= 0)
			continue ;
		if (ft_strstr(cl, "$?"))
		{
			expanded_input = ft_expand_status_var(cl, status);
			if (expanded_input != cl)
			{
				free(cl);
				cl = expanded_input;
			}
		}
		if (!g_sigint_received && ft_strchr(OP_STR2, cl[ft_strlen(cl) - 1]))
			cl = ft_heredoc_op(cl, cl[ft_strlen(cl) - 1]);
		cl = ft_check_prnts(cl);
		if (!cl && !g_sigint_received)
			return (free(cl), rl_clear_history(), 2);
		add_history(cl);
		if (g_sigint_received)
		{
			g_sigint_received = 0;
			continue ;
		}
		//printf("cl = %s\n", cl);
		cli = ft_tokens(cl, envp);	
		//ft_print_list(cli);
		if (cli)
			status = ft_execute(cli);
		ft_free_list(&cli);
	}
	return (free(cl), rl_clear_history(), 0);
}

int	main(int argc, char **argv, char **envp)
{
	extern int rl_catch_signals;
	
	ft_set_sig(PARENT);
	rl_catch_signals = 0;
	return (ft_exec_shell(envp));
}