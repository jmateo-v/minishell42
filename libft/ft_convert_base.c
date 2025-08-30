/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:41:05 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/05 12:11:16 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Returns the result of converting the string nbr from base base_from to base
 * base_to. nbr, base_from, and base_to may be read-only. nbr will follow the
 * same rules as ft_atoi_base (from another module). Beware of the characters
 * ’+’, ’-’, and whitespaces. The number represented by nbr must fit inside an
 * int. If a base is invalid, NULL should be returned. The returned number must
 * be prefixed only by a single and unique ’-’ if necessary; no whitespaces,
 * no ’+’. */

#include "libft.h"

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

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		num;
	char	*result;

	if (ft_errors(base_from) || ft_errors(base_to))
		return (NULL);
	num = ft_atoi_base(nbr, base_from);
	result = ft_convert_int(num, base_to);
	return (result);
}
