/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:54:27 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/21 15:02:18 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The strstr() function finds the first occurrence of the substring needle in
 * the string haystack. The terminating null bytes ('\0') are not compared. */

char	*ft_strstr(const char *str, const char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	if (!*to_find)
		return ((char *)str);
	while (str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j])
		{
			j++;
			if (!to_find[j])
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
