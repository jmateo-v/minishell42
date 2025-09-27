/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:29:22 by rafael-m          #+#    #+#             */
/*   Updated: 2025/09/27 11:13:21 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* DESCRIPTION
       The  strdup()  function  returns  a  pointer to a new string which is a
       duplicate of the string s.  Memory for the new string is obtained with
       malloc(3), and can be freed with free(3).

       The strndup() function is similar, but copies at most n bytes.  If s is
       longer than n, only n bytes are copied, and  a terminating null byte
       ('\0') is added.

       RETURN VALUE
       On success, the strdup() function returns a pointer to the duplicated
       string.  It returns NULL if insufficient  memory was available, with
       errno set to indicate the cause of the error.
 */

#include "libft.h"
#include <string.h>

char	*ft_strndup(const char *src, size_t n)
{
	char	*dest;

	if (!src)
		return (NULL);
	if (n <= 0)
		return (NULL);
	dest = (char *)ft_calloc(n + 1, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, n + 1);
	return (dest);
}
/*
int main(void)
{
    char*s = ft_strndup("HOLAQUETAL", 5);
    char*s1 = strndup("HOLAQUETAL", 5);

    printf ("s =  %s\ns1 = %s\n", s, s1);
}*/
