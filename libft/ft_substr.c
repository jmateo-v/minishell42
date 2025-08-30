/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:15:12 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/09 16:08:31 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdio.h>

Reserva (con malloc(3)) y devuelve una substring de la string ’s’.
La substring empieza desde el índice ’start’ y tiene una longitud máxima ’len’.

RETURN
La substring resultante. NULL si falla la reserva de memoria.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	lg;

	i = 0;
	if (!s || len <= 0)
		return (NULL);
	lg = ft_strlen((char *)s);
	if (start > lg)
		return (result = ft_calloc(1, 1));
	if (len > lg - start)
		len = lg - start;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
int	main(void)
{
	char	*result;

	result = ft_substr("1", 42, 42000);
	printf("result = %s\n", result);
	free (result);
}*/
