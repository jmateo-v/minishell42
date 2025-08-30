/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:28:51 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/16 16:16:29 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <ctype.h>

 checks for a digit (0 through 9). */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}
/*
int	main(void)
{
	char	c = '1';

	printf("ft = %d\n", ft_isdigit(c));
	printf("s = %d\n", isdigit(c));
}*/
