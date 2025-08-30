/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:45:33 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/05 12:11:46 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Muestra una secuencia de caracteres en la pantalla. Si esta secuencia
 * contiene caracteres no imprimibles, deberán se muestran en formato
hexadecimal (en minúsculas) precedidos de una barra invertida (backslash). */

void	ft_putstr_non_printable(char *str)
{
	unsigned char		c;
	char				*hex;

	hex = "0123456789abcdef";
	while (*str)
	{
		c = (unsigned char)*str;
		if (c < 32 || c == 127)
		{
			write(1, "\\", 1);
			ft_putchar(hex[(c / 16)]);
			ft_putchar(hex[(c % 16)]);
		}
		else
			write(1, str, 1);
		str++;
	}
}
