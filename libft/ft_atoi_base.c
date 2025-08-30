/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:22:59 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/05 12:14:28 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Convierte el principio de la cadena apuntada por str en un entero de tipo
 * int. str está en una base específica pasada como segundo argumento de la
 * función. Si un parámetro contiene un error, la función devuelve 0. Un error
 * puede ser:
	◦ la base está vacía o su tamaño es 1;
	◦ la base contiene dos veces el mismo carácter;
	◦ la base contiene los caracteres + o - o espacios; */

static int	ft_pos(char pos, char *base)
{
	int	lg;
	int	i;

	i = 0;
	lg = 0;
	while (base[i])
	{
		if (pos == base[i])
			return (lg);
		lg++;
		i++;
	}
	return (-1);
}

static int	ft_errors(char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!base)
		return (0);
	if (ft_strlen(base) == 1)
		return (1);
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (1);
		j = 0;
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

static int	ft_sign(int *index, int *lg, char first_pos)
{
	int	sign;

	sign = 1;
	if (first_pos == '-')
	{
		(*index)++;
		(*lg)--;
		sign = -1;
	}
	return (sign);
}

int	ft_atoi_base(char *str, char *base)
{
	int	r;
	int	i;
	int	size_b;
	int	lg;
	int	sign;

	i = 0;
	r = 0;
	if (!base || ft_errors(base) || !str)
		return (0);
	size_b = ft_strlen(base);
	lg = ft_strlen(str) - 1;
	sign = ft_sign(&i, &lg, str[0]);
	while (str[i] && lg >= 0)
	{
		if (ft_pos(str[i], base) == -1)
			return (0);
		r = r + (ft_pos(str[i], base)) * (ft_power(size_b, lg));
		i++;
		lg--;
	}
	return (r * sign);
}
