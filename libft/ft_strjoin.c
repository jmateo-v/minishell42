/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:59:52 by rafael-m          #+#    #+#             */
/*   Updated: 2025/05/08 11:11:12 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>

Reserva (con malloc(3)) y devuelve una nueva
string, formada por la concatenación de ’s1’ y
’s2’.

RETURN
La nueva string. NULL si falla la reserva de memoria.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		lg;
	int		lgs1;
	int		i;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	lg = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	lgs1 = ft_strlen((char *)s1);
	result = (char *)malloc((lg + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, (char *)s1, lgs1 + 1);
	while (s2[i])
	{
		result[lgs1 + i] = s2[i];
		i++;
	}
	result[lg] = '\0';
	return (result);
}

// int	main(void)
// {
// 	char	*s = ft_strdup("HOLA");
// 	char    *s2 = ft_strdup("QUE TAL");
// 	char	*r;

// 	r = ft_strjoin("","");
// 	printf("ft = %s\n", r);
// 	free (r);
// }
