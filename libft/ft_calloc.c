/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:50:47 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/19 16:02:33 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdio.h>

The  calloc() function allocates memory for an array of nmemb elements of size
bytes each and returns a pointer to the allocated memory.  The memory is set to
zero.  If nmemb or size is 0, then calloc()  returns either NULL, or a unique
pointer value that can later be successfully passed to free().  If the
multiplication of nmemb and size would result in integer overflow, then
calloc() returns  an  error.  By contrast, an integer overflow would not be
detected in the following call to malloc(), with the result that an incorrectly
sized block of memory would be allocated:

           malloc(nmemb * size);

RETURN VALUE
The  malloc()  and calloc() functions return a pointer to the allocated memory,
which is suitably aligned for any built-in type.  On error, these functions
return NULL.  NULL may also be returned by  a  successful  call to malloc()
with a size of zero, or by a successful call to calloc() with nmemb or size
equal to zero.
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (nmemb == 0 || size == 0)
	{
		result = malloc(0);
		return (result);
	}
	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	result = malloc(nmemb * size);
	if (!result)
		return (NULL);
	ft_bzero(result, nmemb * size);
	return (result);
}
/*
int	main(void)
{
	size_t	size = 0;
	size_t	nmemb = 0;
	size_t	i = 0;
	char	*r1 = (char *)ft_calloc(nmemb, size);
	char    *r2 = (char *)calloc(nmemb, size);

	while (i < (nmemb * size))
	{
		r1[i] = 65;
		r2[i] = 65;
		i++;
	}
	printf("r1 = %p\n", r1);
	printf("SIZE_MAX = %lu\n", SIZE_MAX);
	printf("r2 = %p\n", r2);
	printf("len r1 = %ld\n", strlen(r2));
	printf("len r2 = %ld\n", strlen(r2));
	printf("r1 = %s\n", r1);
	printf("r2 = %s\n", r2);
	free (r1);
	free (r2);
}*/
