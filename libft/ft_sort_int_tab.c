/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:13:09 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/21 14:26:08 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Ordena un array de int en orden ascendente */

void	ft_sort_int_tab(int *tab, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < size - 1)
	{
		i = 0;
		while (i < size - j - 1)
		{
			if (tab[i + 1] < tab[i])
				ft_swap(&tab[i], &tab[i + 1]);
			i++;
		}
		j++;
	}
}
