/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:16:39 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/19 16:16:30 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdio.h>

The  strchr() function returns a pointer to the first occurrence of the
character c in the string s.

RETURN VALUE
The strchr() and strrchr() functions return a pointer to the matched character
or  NULL  if  the character is not found.  The terminating null byte is
considered part of the string, so that if c is specified as '\0', these
functions return a pointer to the terminator.
*/

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if ((unsigned char)c == *s)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == *s)
		return ((char *)s);
	return (NULL);
}
/*
int	main(void)
{
//	char	c = 'e';
	char s[] = "tripouille";

	printf("s ft = %p\n", ft_strchr(s, 't' + 256));
	printf("*s = %p\n", strchr(s, 't' + 256));
}*/
