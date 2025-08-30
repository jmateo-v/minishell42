/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:38:47 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/19 16:12:59 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>
#include <stdio.h>
#include <stdlib.h>


The  memset()  function  fills the first n bytes of the memory area pointed
to by s with the constant byte c. */

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;

	i = 0;
	d = (unsigned char *)s;
	while (i < n)
	{
		d[i] = c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	int	c = 98;
	size_t	n = 10;
	char	s[25] = "111111111111111111111111";
	char	s2[25] = "111111111111111111111111";

	ft_memset(s, c, n);
	printf("s = %s\n", s);
	memset(s2, c, n);
	printf("s2 = %s\n", s2);
}
*/
