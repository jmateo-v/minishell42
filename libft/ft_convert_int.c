/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:15:13 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/05 12:10:01 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

/* Convierte un int pasado como parámetro a un string resultado de la conversión
 * del int a la base pasada como string como segundo parámetro */

static int	ft_errors(char *base)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!base)
		return (1);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (1);
		while (base[j])
		{
			if (base[j] == base[i] && j != i)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

char	*ft_convert_int(long nbr, char *base)
{
	unsigned char	*result;
	size_t			base_len;
	int				nbr_len;

	if (!base || ft_errors(base))
		return (NULL);
	base_len = ft_strlen(base);
	nbr_len = ft_nbr_base_len(nbr, base_len);
	result = (unsigned char *)ft_calloc(nbr_len + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	if (nbr == 0)
		result[0] = base[0];
	while (nbr > 0)
	{
		result[--nbr_len] = base[nbr % base_len];
		nbr = nbr / base_len;
	}
	return ((char *)result);
}
/*
int	main(void)
{
	char *result;

	result = ft_convert_int(-123, "0123456789");
	printf("r = %s\n", result);
	free (result);
}*/
