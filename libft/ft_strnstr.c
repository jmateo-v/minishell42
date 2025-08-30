/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:59:47 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/16 17:52:23 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <string.h>
#include <stdio.h>

The strnstr() function locates the first occurrence of the null-terminated
string little in the string big, where not more than len characters are
searched.  Characters that appear after a ‘\0’ character are not searched.
Since the strnstr() function is a FreeBSD specific API, it should only be used
when portability is not a concern.

RETURN VALUES
If little is an empty string, big is returned; if little occurs nowhere in big,
NULL is returned; otherwise a pointer to the first character of the first
occurrence of little is returned.
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	j;
	size_t	i;
	size_t	lg;

	j = 0;
	i = 0;
	lg = ft_strlen((char *)needle);
	if (lg == 0)
		return ((char *)haystack);
	while (haystack[i] && i < n)
	{
		j = 0;
		while (j < lg && (i + j) < n && needle[j] == haystack[i + j])
		{
			j++;
			if (j == lg)
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	printf("s ft = %p\n", ft_strnstr("asdasdlad", "asd", 123));
	printf("s = %p\n", strstr("asdasdlad", "asd"));
}*/
