/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:27:36 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/04 12:26:07 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

/*
DESCRIPTION
       The atoi() function converts the initial portion of the string pointed
       to by nptr to int.  The behavior is the same as

           strtol(nptr, NULL, 10);

       except that atoi() does not detect errors.

       The  atol()  and atoll() functions behave the same as atoi(), except
       that they convert the initial portion of the string to their
       return type of long or long long.

RETURN VALUE
       The converted value or 0 on error.
*/

long	ft_atol(const char *str)
{
	int		sign;
	int		i;
	long	r;
	int		digit;

	i = 0;
	r = 0;
	sign = 1;
	if (!str)
		return (0);
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = 1 - 2 * (str[++i] == '-');
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (sign == 1 && (r > (LONG_MAX - digit) / 10))
			return (0);
		if (sign == -1 && (r < (LONG_MIN + digit) / 10))
			return (0);
		r = r * 10 + (str[i++] - '0');
	}
	return (sign * r);
}
