/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:28:01 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/21 16:12:29 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Devuelve la el resultado de elevar una base a una potencia (power) */

int	ft_power(int base, int power)
{
	int	result;
	int	i;

	result = 1;
	i = 0;
	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	while (i < power)
	{
		result *= base;
		i++;
	}
	return (result);
}
