/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:31:47 by rafael-m          #+#    #+#             */
/*   Updated: 2025/07/20 22:32:23 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  strncpy()  function is similar, except that at most n bytes of src are
 * copied.  Warning: If there is no null byte among the first n bytes of src,
 * the string placed  in  dest  will  not  be null-terminated.

 If  the  len  of src is less than n, strncpy() writes additional null bytes
 to dest to ensure that a total of n bytes are written.

 RETURN VALUE
	Returns a pointer to the destination string dest.
*/

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*start;

	start = dest;
	while (*src && n > 0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	while (n > 0)
	{
		*dest = '\0';
		dest++;
		n--;
	}
	return (start);
}
