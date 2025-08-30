/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:35:16 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/19 16:40:57 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <string.h>
#include <stdio.h>

The  memchr() function scans the initial n bytes of the memory area pointed to
by s for the first instance of c.  Both c and the bytes of the memory area
pointed to by s are  interpreted  as  unsigned char.

RETURN VALUE
The memchr() and memrchr() functions return a pointer to the matching byte or
NULL if the character does not occur in the given memory area.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	int	c = 'r';
	char	s[] = "hola";
//	int	s2[]= {-56, 5, 5};
	size_t	n = -5;

	printf("s ft = %p\n", ft_memchr(s, c, n));
	printf("s = %p\n", memchr(s, c, n));
}*/
