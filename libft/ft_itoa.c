/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:06:03 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/05 12:07:20 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

size_t	ft_intlen(long n)
{
	size_t	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*result;
	long	nbr;

	nbr = (long)n;
	len = ft_intlen(n);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	len--;
	if (nbr < 0)
	{
		nbr = -nbr;
		result[0] = '-';
	}
	while (nbr > 9)
	{
		result[len] = (nbr % 10) + 48;
		nbr = nbr / 10;
		len --;
	}
	result[len] = nbr + 48;
	return (result);
}
