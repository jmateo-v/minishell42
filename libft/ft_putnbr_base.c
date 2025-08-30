/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:05:29 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/05 12:04:00 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
/* Muestra un número en el terminal en una base determinada. Se proporciona
 * este número en forma de un int y la base en forma de un string. La base
 * contiene todos los símbolos que se pueden utilizar para mostrar el número.
 *
 * Si un parámetro contiene un error la función no muestra nada.
 * Un error puede ser:
	◦ la base está vacía o su tamaño es 1;
	◦ la base contiene dos veces el mismo carácter;
	◦ la base contiene los caracteres + o - */

static int	ft_errors(char *base)
{
	unsigned int	i;
	unsigned int	j;
	size_t			base_len;

	i = 0;
	j = 0;
	base_len = ft_strlen(base);
	if (base_len <= 1)
		return (1);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
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

void	ft_putnbr_base(long nbr, char *base)
{
	size_t			base_len;
	int				nbr_len;
	unsigned char	*result;
	int				neg;

	if (!base || ft_errors(base))
		return ;
	base_len = ft_strlen(base);
	neg = ft_neg(nbr);
	nbr_len = ft_nbr_base_len(nbr, base_len) - neg;
	if (neg)
		nbr = -nbr;
	result = (unsigned char *)ft_calloc(nbr_len + 1, sizeof(char));
	if (!result)
		return ;
	if (nbr == 0)
		result[0] = base[0];
	while (nbr > 0)
	{
		result[--nbr_len] = base[nbr % base_len];
		nbr = nbr / base_len;
	}
	write(1, result, ft_strlen((char *)result));
	free (result);
}
/*
int main(void)
{
	char	*ptr = "qwe";
	unsigned long	nbr;

	nbr = (unsigned long)ptr;
	printf("printf = %p", ptr);
	ft_putnbr_base(nbr, "0123456789ABCDEF");
	write(1, "\n", 1);
	ft_putnbr_base(0, "0123456789"); //Imprime: 0
	write(1, "\n", 1);
	ft_putnbr_base(-255, "0123456789ABCDEF"); // Imprime: -FF
	write(1, "\n", 1);
	ft_putnbr_base(42, "01"); // Imprime: 101010
	write(1, "\n", 1);
	ft_putnbr_base(123456, "01234567"); // Imprime: 361100
	write(1, "\n", 1);
}
*/
