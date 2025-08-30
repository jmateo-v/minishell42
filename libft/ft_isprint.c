/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:28:13 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/16 16:17:37 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <ctype.h>

 checks for any printable character including space. */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	return (0);
}
/*
int	main(void)
{
	int	c = 98;

	printf("ft = %d\n", ft_isprint(c));
	printf("s = %d\n", isprint(c));
}*/
