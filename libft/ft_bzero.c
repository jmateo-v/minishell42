/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:38:06 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/19 16:02:11 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>
#include <stdlib.h>

 The  bzero()  function  erases  the  data  in  the n
 bytes of the memory starting at the location
       pointed to by s, by writing zeros (bytes containing
       '\0') to that area. */

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*d;

	d = (unsigned char *)s;
	ft_memset(d, '\0', n);
	return (s);
}
/*
int	main(void)
{
	size_t	n = 25;
	char	s[10] = "1232131";
	char	s2[10] = "1232131";

	ft_bzero(s, n);
	printf("s = %s\n", s);
	bzero(s2, n);
	printf("s2 = %s\n", s2);
}
*/
