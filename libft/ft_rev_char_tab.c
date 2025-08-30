/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_char_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:18:24 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/05 12:04:33 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Revierte el orden de los carácteres de un string */

void	ft_rev_char_tab(char *tab)
{
	int	t;
	int	end;
	int	start;

	end = ft_strlen(tab) - 1;
	start = 0;
	while (start < end)
	{
		t = tab[start];
		tab[start] = tab[end];
		tab[end] = t;
		++start;
		--end;
	}
}
