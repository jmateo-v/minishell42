/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:21:20 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/19 16:40:14 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*#include <stdio.h>

static char	to_uppercase_i(unsigned int index, char c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c - 32 + index);
	}
	return (c);
}
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	lg;
	char	*r;

	i = 0;
	lg = ft_strlen((char *)s);
	r = (char *)malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (!r)
		return (NULL);
	while (i < lg)
	{
		r[i] = f((unsigned int)i, s[i]);
		i++;
	}
	r[i] = '\0';
	return (r);
}
/*
int	main(void)
{
	char	*s;

	s = ft_strmapi("asdasda", to_uppercase_i);
	printf("ft_strmapi = %s\n", s);
	free (s);
}
*/
