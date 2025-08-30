/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:32:44 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/09 13:33:22 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *s, int c, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (!s || !n)
	{
		return (NULL);
	}
	while (s[i] && i < n)
	{
		if ((unsigned char)c == s[i])
			return ((char *)&s[i]);
		i++;
	}
	if (i < n && (unsigned char)c == s[i])
		return ((char *)&s[i]);
	return (NULL);
}
