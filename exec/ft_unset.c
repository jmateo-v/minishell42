/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:54:04 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/09/15 11:12:09 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_unsetenv(t_shenv **env, const char *key)
{
    t_shenv *curr;
    t_shenv *prev;
    int len;

    curr = *env;
    prev = NULL;
    len = ft_strlen(key);
    while (curr)
    {
        if(!ft_strncmp(curr->var, key, len) && curr->var[len] == '=')
        {
            if (prev)
                prev->next = curr->next;
            else
                *env = curr->next;
            free(curr->var);
            free(curr);
            return (0);
        }
        prev = curr;
        curr = curr->next;
    }
    return (1);
}
int ft_unset(char **args, t_shenv **env)
{
    int i;
    int ret;

    ret = 0;
    if (!args || !env)
        return (1);
    i = 1;
    while(args[i])
    {
        ft_unsetenv(env, args[i]);
        i++;
    }
    return (ret);
}