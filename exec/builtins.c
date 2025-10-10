/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:48:38 by dogs              #+#    #+#             */
/*   Updated: 2025/10/10 16:25:20 by dogs             ###   ########.fr       */
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
        printf("%s", args[i]);
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
    int i;

    if (!str || !*str)
        return 0;

    i = 0;
    if (str[0] == '+' || str[0] == '-')
        i = 1;

    if (!str[i])
        return 0;

    for (; str[i]; i++)
    {
        if (!ft_isdigit((unsigned char)str[i]))
            return 0;
    }
    return 1;
}

#include <limits.h>

long long   ft_atoll(const char *str)
{
    long long           result;
    int                 sign;
    unsigned long long  tmp;

    result = 0;
    sign = 1;

    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;

    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }

    tmp = 0;
    while (*str && *str >= '0' && *str <= '9')
    {
        int digit = *str - '0';
        if (tmp > (ULLONG_MAX - digit) / 10)
        {
            if (sign == 1)
                return LLONG_MAX;
            else
                return LLONG_MIN;
        }
        tmp = tmp * 10 + digit;
        str++;
    }
    result = (long long)(tmp * sign);
    return result;
}

int ft_exit(char **args, int last_status)
{
    long long val;
    int status = last_status;

    if (isatty(STDIN_FILENO))
        write(1, "exit\n", 5);

    if (args[1])
    {
        if (!is_numeric(args[1])) {
            dprintf(2, "exit: %s: numeric argument required\n", args[1]);
            exit(2);
        }
        if (args[2]) {
            dprintf(2, "exit: too many arguments\n");
            return 1;
        }
        val = ft_atoll(args[1]);
        status = (unsigned char)val;
    }

    exit(status);
}


