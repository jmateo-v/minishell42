/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:53:27 by rafael-m          #+#    #+#             */
/*   Updated: 2025/07/20 22:32:23 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>
#include <string.h>


The strlcat() function appends the NUL-terminated string src to the end of dst.
It will append at most size - strlen(dst) - 1 bytes, NUL-terminating the
result.
     
RETURN VALUES
The strlcpy() and strlcat() functions return the total len of the string
they tried to create. For strlcpy() that means the len of src.  For
strlcat() that means the initial len of dst plus the len of src.  While
this may seem somewhat confusing, it was done to make truncation detection
simple.

Note, however, that if strlcat() traverses size characters without finding a
NUL, the len of the string is considered to be size and the destination
string will not be NUL-terminated (since there was no space for the NUL).  This
keeps strlcat() from running off the end of a string.  In practice this should
not happen (as it means that either size is incorrect or that dst is not a
proper “C” string).  The check exists to prevent potential security problems in
incorrect code.
     */

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	lg;
	size_t	lg2;

	i = 0;
	lg = ft_strlen(dest);
	lg2 = ft_strlen(src);
	if (size <= lg)
		return (size + lg2);
	while (src[i] && (i + lg < size - 1))
	{
		dest[lg + i] = src[i];
		i++;
	}
	dest[lg + i] = '\0';
	return (lg + lg2);
}
/*
int	main(void)
{
	char	dest[20] = "";
	char    dest2[20] = "hola";
	char    dest3[20] = "hola";
	char    dest4[20] = "hola";
	char    dest5[20] = "hola";
	char	src[6] = "adios";
	int	result;

	result = ft_strlcat(dest, src, 3);
	printf("dest = %s\n", dest);
	printf("result = %d\n", result);
	result = ft_strlcat(dest2, "", 12);
	printf("dest2 = %s\n", dest2);
	printf("result2 = %d\n", result);
	result = ft_strlcat(dest3, src, 3);
	printf("dest3 = %s\n", dest3);
	printf("result3 = %d\n", result);
	result = ft_strlcat(dest4, src, 6);
	printf("dest4 = %s\n", dest4);
	printf("result4 = %d\n", result);
	result = ft_strlcat(dest5, src, 10);
	printf("dest5 = %s\n", dest5);
	printf("result5 = %d\n", result);
}
*/
