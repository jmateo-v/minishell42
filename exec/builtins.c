/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:48:38 by dogs              #+#    #+#             */
/*   Updated: 2025/10/09 15:40:33 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd(char **args)
{
    char cwd[PATH_MAX];
    (void)args;
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("pwd");
        return (1);
    }
    printf("%s\n", cwd);
    return (0);
}

int ft_echo(char **args)
{
    int i = 1;
    int new_line = 1;

    if (args[i] && ft_strcmp(args[i], "-n") == 0)
    {
        new_line = 0;
        i++;
    }
    while (args[i])
    {
        // Print the argument (even if it's an empty string)
        printf("%s", args[i]);

        // If there's another argument after this, print a space
        if (args[i + 1] != NULL)
            printf(" ");

        i++;
    }
    if (new_line)
        printf("\n");
    return (0);
}

int ft_env(char **env)
{
    int i;

    i = 0;
    if (!env)
        return (1);
    while(env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
    ft_free_d(env);
    return (0);
}
int is_numeric(const char *str)
{
    if (!str || !*str)
        return 0;

    int i = 0;
    if (str[0] == '+' || str[0] == '-')
        i = 1;

    for (; str[i]; i++) {
        if (!ft_isdigit(str[i]))
            return 0;
    }
    return 1;
}

int ft_exit(char **args)
{
    int status = 0;

    // Only print "exit" if running in interactive mode
    if (isatty(STDIN_FILENO))
        write(1, "exit\n", 5);

    if (args[1]) {
        if (!is_numeric(args[1])) {
            write(2, "exit: ", 6);
            write(2, args[1], ft_strlen(args[1]));
            write(2, ": numeric argument required\n", 29);
            exit(255);
        }
        status = ft_atoi(args[1]);
    }

    exit(status);
    return 0; // unreachable
}

