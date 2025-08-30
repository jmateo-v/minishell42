/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:52:27 by dogs              #+#    #+#             */
/*   Updated: 2025/08/30 12:53:55 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cd(char **args, char ***env)
{
    char cwd[PATH_MAX];
    char *target;

    target = NULL;
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("cd: getcwd");
        return (1);
    }
    if (!args[1] || !args[1][0])
        target = ft_getenv(*env, "HOME");
    else if (strcmp(args[1], "-") == 0)
        target = ft_getenv(*env, "OLDPWD");
    else
        target = args[1];
    
    if (!target)
    {
        ft_putstr_fd("cd: target not found\n", 2);
        return(1);
    }
    if (chdir(target) != 0)
    {
        perror("cd");
        return (1);
    }
    ft_setenv(env, "OLDPWD", cwd);
    if (getcwd(cwd, sizeof(cwd)))
    {
        ft_setenv(env, "PWD", cwd);
        printf("CD set PWD to: %s\n", ft_getenv(*env, "PWD"));
    }
    
    return (0);
}
char *ft_getenv(char **env, const char *key)
{
    int len;

    len = strlen(key);
    while (*env)
    {
        if (!strncmp(*env, key, len) && (*env)[len] == '=')
            return(*env + len + 1);
        env++;
    }
    return NULL;
}
static int env_len(char **env)
{
    int i;
    i = 0;
    while(env && env[i])
        i++;
    return i;
}
int ft_setenv(char ***envp, const char *key, const char *value)
{
    int i;
    char *new_var;
    int key_len;
    int size;
    char **new_env;

    if (!envp || !key || !value)
        return (1);
    key_len = ft_strlen(key);
    new_var = malloc(key_len + ft_strlen(value) + 2);
    if (!new_var)
        return(perror("malloc"), 1);
    ft_strcpy(new_var, key);
    new_var[key_len] = '=';
    ft_strcpy(new_var + key_len + 1, value);
    i = 0;
    while((*envp)[i])
    {
        if (!ft_strncmp((*envp)[i], key, key_len) && (*envp)[i][key_len] == '=')
        {
            free((*envp)[i]);
            (*envp)[i] = new_var;
            return (0);
        }
        i++;
    }
    size = env_len(*envp);
    new_env = malloc(sizeof(char *) * (size + 2));
    if (!new_env)
        return(free(new_var), perror("malloc"), 1);
    i = 0;
    while (i < size)
    {
        new_env[i] = ft_strdup((*envp)[i]);
        if (!new_env[i])
            return (free(new_var), perror("malloc"), 1);
        i++;
    }
    new_env[i++] = new_var;
    new_env[i] = NULL;
    free(*envp);
    *envp = new_env;

    return(0);
    
}