/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:28:07 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/19 16:13:22 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;

	d = (unsigned char *)dest;
	s = (unsigned const char *)src;
	if (d == s || n == 0)
		return (dest);
	if (d < s)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d = d + n;
		s = s + n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}
/*
int	main(void)
{
	size_t  n = 5;
//	char	*dest;
//	char    *dest2;
	char	src[] = "lorem ipsum dolor sit amet";
	char    src2[] = "lorem ipsum dolor sit amet";


	ft_memmove(src, "consectetur", n);
	memmove(src2, "consectetur", n);
	printf("dest = %s\n", src);
	printf("dest2 = %s\n", src2);

	n = 10;
	dest = src + 1;
        dest2 = src + 1;
	src = "con\0sec\0\0te\0tur";
	ft_memmove(dest, src, n);
        memmove(dest2, src, n);
	printf("dest = %s\n", dest);
        printf("dest2 = %s\n", dest2);

	n = 8;
	dest = src + 1;
        dest2 = src + 1;
	src = "lorem ipsum dolor sit amet";
	ft_memmove(dest, src, n);
        memmove(dest2, src, n);
	printf("dest = %s\n", dest);
        printf("dest2 = %s\n", dest2);

	n = 27;
	dest = src + 1;
        dest2 = src + 1;
	ft_memmove(dest, src, n);
        memmove(dest2, src, n);
	printf("dest = %s\n", dest);
        printf("dest2 = %s\n", dest2);

	n = 27;
	dest = src + 1;
        dest2 = src + 1;
	ft_memmove("", src, n);
	printf("dest = %s\n", dest);
	printf("dest2 = %p\n", memmove("", src, n));
}*/
