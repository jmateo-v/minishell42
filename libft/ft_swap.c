/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:06:20 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/21 14:07:09 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Intercambia el contenido de dos enteros cuyas direcciones
se utilicen como parámetro. */

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
