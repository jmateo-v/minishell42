/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:48:38 by dogs              #+#    #+#             */
/*   Updated: 2025/08/28 11:02:17 by dogs             ###   ########.fr       */
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
    int i;
    int new_line;

    i = 1;
    new_line = 1;
    
    while (args[i])
    {
        if (args[i] && ft_strcmp(args[i], "-n") == 0)
        {
            new_line = 0;
            i++;
        }
        else
        {
            printf("%s", args[i]);
            if (args[i + 1])
                printf(" ");
        i++;
        }
    }
    if (new_line)
        printf("\n");
    
    return (0);
}
int ft_env(char **env)
{
    int i;
    if (!env)
        return (1);
    while(env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (0);
}
int ft_exit(void)
{
    printf("exit\n");
    exit(0);
    return (0);
}
