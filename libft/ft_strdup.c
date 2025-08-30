/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:40:15 by rafael-m          #+#    #+#             */
/*   Updated: 2025/05/08 10:59:29 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
/*
The  strdup()  function  returns  a pointer to a new string which is a
duplicate of the string s. Memory for the new string is obtained with
malloc(3), and can be freed with free(3).

RETURN VALUE
On success, the strdup() function returns a pointer to the duplicated string.
It returns NULL if insufficient memory was available, with errno set to
indicate the cause of the error.
*/

char	*ft_strdup(const char *src)
{
	char		*dest;
	size_t		size;

	if (!src)
		return (NULL);
	size = ft_strlen(src);
	dest = (char *)ft_calloc((size + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, size + 1);
	return (dest);
}
/*
int	main(void)
{
	char	*str = "Hola\0quetal";
	char	*result;
	int	size;
	char	*result2;
	int	size2;

	result = ft_strdup(str);
	size = ft_strlen(result);
	result2 = strdup(str);
	size2 = strlen(result2);
	printf("result2 = %p\n", result2);
	printf("size2 = %d\n", size2);
	printf("result2 = %s\n", result2);
	printf("result = %p\n", result);
	printf("size = %d\n", size);
	printf("result = %s\n", result);
	free (result);
	return (0);
}
*/
