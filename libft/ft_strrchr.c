/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:33:10 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/16 17:42:11 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdio.h>
#include <string.h>

The strrchr() function returns a pointer to the last occurrence of the
character c in the  string s.

RETURN VALUE
The strchr() and strrchr() functions return a pointer to the matched character
or  NULL  if  the character is not found.  The terminating null byte is
considered part of the string, so that if c is specified as '\0', these
functions return a pointer to the terminator.
*/

char	*ft_strrchr(const char *s, int c)
{
	int	lg;

	lg = ft_strlen((char *)s);
	while (lg >= 0)
	{
		if ((char)c == s[lg])
			return ((char *)&s[lg]);
		lg--;
	}
	return (NULL);
}
/*
int	main(void)
{
	int	c = 'o';
//	char	s[] = {'h', 'o', 'l', 'a'};
	char	*s2 = "";

	printf("s ft = %p\n", ft_strrchr(s2, c));
	printf("s = %p\n", strrchr(s2, c));
}*/
