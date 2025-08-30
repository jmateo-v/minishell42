/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:28:02 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/04 12:23:33 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

The  atoi()  function  converts the initial portion of the string pointed to by
nptr to int.  The behavior is the same as

           strtol(nptr, NULL, 10);

except that atoi() does not detect errors.

RETURN VALUE
       The converted value or 0 on error.
*/

int	ft_atoi(const char *str)
{
	int	sign;
	int	r;
	int	i;
	int	digit;

	r = 0;
	i = 0;
	sign = 1;
	if (!str)
		return (0);
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = 1 - 2 * (str[i++] == '-');
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (sign == 1 && r > (INT_MAX - digit) / 10)
			return (0);
		if (sign == -1 && r > (INT_MIN - digit) / 10)
			return (0);
		r = r * 10 + (str[i++] - '0');
	}
	return (sign * r);
}
/*
int     main(void)
{
        char    *nbr = "  \t  -0\t12";
        int     r;

        r = ft_atoi(nbr);
        printf("ft_atoi = %d\n", r);
        r = atoi(nbr);
        printf("atoi = %d\n", r);
}*/
