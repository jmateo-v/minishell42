/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:50:11 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/16 20:54:17 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
/*#include <stdio.h>

The  memcmp() function compares the first n bytes (each interpreted as unsigned
char) of the memory areas s1 and s2.

RETURN VALUE
The memcmp() function returns an integer less than, equal to, or greater than
zero if the first n bytes  of  s1  is  found, respectively, to be less than, to
match, or be greater than the first n bytes of s2.

For a nonzero return value, the sign is determined by the sign  of  the 
difference  between  the first pair of bytes (interpreted as unsigned char)
that differ in s1 and s2.

If n is zero, the return value is zero.
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str;
	const unsigned char	*str2;

	i = 0;
	str = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (str[i] != str2[i])
			return (str[i] - str2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	size_t	n = -12345;
	printf("n = %zu\n", n);
//	int	s[] = {'h', 'o', 'l', 'a'};
	char	*str = "holaas";
//	int     s2[] = {'h', 'o', 'l', 'a'};
	char    *str2 = "holaas";

	printf("s ft = %d\n", ft_memcmp(str2, str, n));
	printf("s = %d\n", memcmp(str2, str, n));
}*/
