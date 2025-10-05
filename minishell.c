/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:19:16 by rafael-m          #+#    #+#             */
/*   Updated: 2025/10/05 18:21:10 by dogs             ###   ########.fr       */
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
void ft_print_tokens(char **tokens)
{
    int i = 0;

    printf("Tokens before parsing:\n");
    while (tokens && tokens[i])
    {
        printf("Token[%d]: '%s'\n", i, tokens[i]);
        i++;
    }
    printf("\n");
}

int	ft_check_prnts(char *line)
{
	size_t		i;
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
				return (-1);
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
	t_cli	*last;

	if (!cli)
		return ;
	last = cli;
	while (last->next)
		last = last->next;
	cli->status = last->status;
	next = cli->next;
	if (next)
	{
		ft_free_list(&next);
		cli->next = NULL;
	}
	free(cli->cmd);
	cli->cmd = NULL;
	free(cli->heredoc);
	cli->heredoc = NULL;
	free(cli->infile);
	cli->infile = NULL;
	free(cli->outfile);
	cli->outfile = NULL;
	if (cli -> args)
	{
		ft_free_d(cli->args);
		cli->args = NULL;
	}
	cli->is_builtin = 0;
	cli->r_mode = 0;
	cli->group = 0;
	cli->op = 0;
}

int	ft_reset_signal(t_cli *cli)
{
	g_sig_rec = 0;
	ft_reset_list(cli);
	cli->last_status = 130;
	return (1);
}

int	ft_read_line(t_cli *cli)
{
	char	*cl;
	t_token	*tokens;
	char buffer[1024];
	ssize_t bytes_read;

	cl = NULL;
	while (1)
	{
		if (cl) 
    	{
        free(cl);
		cl = NULL;
    	}
		//printf("status = %d\n", cli->last_status);
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		{
			rl_outstream = stderr;
			cl = readline("\033[1;32mminishell\033[0m$ ");
			if (!cl)
			{
				write(1, "exit\n", 5);
				break;
			}
		}
		else
		{
			bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
			if (bytes_read <= 0)
			{
				write(1, "exit\n", 5);
				break;
			}
			buffer[bytes_read] = '\0';
			if (bytes_read > 0 && buffer[bytes_read - 1] == '\n')
				buffer[bytes_read - 1] = '\0';
			cl = malloc(bytes_read + 1);
			if (!cl)
				return (perror("malloc error"), 1);
			ft_strcpy(cl, buffer);
		}
		if (g_sig_rec && ft_reset_signal(cli))
			continue ;
		add_history(cl);
		tokens = ft_tokens(cl, cli);
		if (!tokens)
		{
			cli->status = 2;
			continue ;
		}
		//ft_print_tokens(tokens);
		cli->status = ft_parse(tokens, cli);
		cli->status = ft_execute(cli);
		if (cl && !isatty(STDIN_FILENO))
		{
		free(cl);
		cl = NULL;
		}
		if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		{
			ft_free_tokens(tokens);
			ft_reset_list(cli);
			rl_clear_history();
			return (cli->status);
		}
		cli->last_status = cli->status;
		//ft_print_list(cli);
		ft_free_tokens(tokens);
		ft_reset_list(cli);
		//ft_free_tokens(tokens, cli->n_tokens);
	}
	
	return (rl_clear_history(), cli->status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shenv		*env;
	extern int 	rl_catch_signals;
	t_cli		*cli;
	int			status;
	
	(void)argc;
	(void)argv;
	ft_set_sig(PARENT);
	rl_catch_signals = 0;
	env = ft_load_env(envp);
	cli = ft_init_node(1, &env, 0);
	if (!cli)
		return (ft_free_env(&env), 2);
	status = ft_read_line(cli);
	ft_free_list(&cli);
	ft_free_env(&env);
	return (status);
}