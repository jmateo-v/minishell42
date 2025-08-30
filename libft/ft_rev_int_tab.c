/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:09:45 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/21 14:25:26 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Invierte un array de int (el primer elemento va el último, etc) */

void	ft_rev_int_tab(int *tab, size_t size)
{
	int	temp;
	int	end;
	int	start;

	end = (int)size - 1;
	start = 0;
	while (start < end)
	{
		temp = tab[start];
		tab[start] = tab[end];
		tab[end] = temp;
		++start;
		--end;
	}
}
