/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:19:16 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/30 13:55:03 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

char	*get_pwd(char *cwd)
{
	char	*home;
	char	*pwd;
	char	*t;

	if (!cwd)
		return (NULL);
	home = ft_strtrim(getenv("HOME"), "HOME=");
	if (!home)
		return (NULL);
	if (!ft_strncmp(home, cwd, ft_strlen(home)))
	{
		t = ft_strtrim(cwd, home);
		pwd = ft_strjoin("~/", t);
		return (free(home), free(t), pwd);
	}
	pwd = ft_strdup(cwd);
	return (free(home), pwd);
}

char	*get_hostname(void)
{
	char	*r;
	char	*buffer;
	char	*t;
	int		fd;

	r = NULL;
	fd = open("/etc/hostname", O_RDONLY);
	buffer = ft_calloc(2, sizeof(char));
	if (fd == -1 || ! buffer)
		return (free(buffer), NULL);
	read(fd, buffer, 1);
	while (buffer[0] != '\n' && buffer[0] != EOF)
	{
		t = r;
		r = ft_strjoin(r, buffer);
		read(fd, buffer, 1);
		free(t);
	}
	return (free(buffer), close(fd), r);
}

char	*ft_prompt(char **envp)
{
	char	*user;
	char	*pwd;
	char	*prompt;
	char	*t;

	if (!envp)
		return (NULL);
	user = ft_strtrim(getenv("USER"), "USER=");
	t = (char *)ft_calloc(4096, sizeof(char));
	if (!t || ! user)
		return (perror("malloc: "), NULL);
	pwd = get_pwd(getcwd(t, 4096));
	free(t);
	prompt = ft_strjoin(user, "@");
	free(user);
	user = get_hostname();
	t = ft_strjoin(prompt, user);
	free(user);
	free(prompt);
	prompt = ft_strjoin(t, ":");
	free(t);
	t = ft_strjoin(prompt, pwd);
	free(prompt);
	prompt = ft_strjoin(t, "$ ");
	return (free(t), free(pwd), prompt);
}

int	ft_exec_shell(struct sigaction *sa, char **envp)
{
	char	*cl;
	char	**tokens;
	char	*prompt;
	t_cli	*cli;
	int	status;
	char *expanded_input;

	status = 0;
	prompt = NULL;
	cl = NULL;
	while (1)
	{
		free(cl);
		free(prompt);
		prompt = ft_prompt(envp);
		cl = readline(prompt);
		if (!cl)
			break ;
		if (g_sigint_received || ft_strlen(cl) <= 0)
		{
			g_sigint_received = 0;
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			continue ;
		}
		if (ft_strstr(cl, "$?"))
		{
			expanded_input = ft_expand_status_var(cl,status);
			if (expanded_input != cl)
			{
				free(cl);
				cl = expanded_input;
				//printf("Expanded input is: %s", cl);
			}
		}
		cli = ft_tokens(cl, envp);
		//ft_print_list(cli);
		if (g_sigint_received)
		{
			g_sigint_received = 0;
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			ft_free_list(&cli); 
			continue ;
		}
		if (cli)
		{
			status = ft_execute(cli);
			//ft_print_list(cli);
		}
		ft_free_list(&cli);
		add_history(cl);
	}
	return (free(prompt), free(cl), rl_clear_history(), 0);
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction sa;
	extern int rl_catch_signals;
    extern int rl_catch_sigwinch;

    rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	ft_set_sig(PARENT);
	ft_exec_shell(&sa, envp);
	return (0);
}