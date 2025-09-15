/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:20:20 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/04 12:21:34 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_one_space_len(char *s)
{
	size_t	i;
	size_t	len;
	size_t	len_s;

	if (!s)
		return (0);
	len = 0;
	i = 0;
	len_s = ft_strlen(s);
	while (ft_isspace(s[i]))
		i++;
	while (i < len_s)
	{
		while (ft_isspace(s[i]) && ((ft_isspace(s[i + 1])) || !s[i + 1]))
		{
			i++;
			continue ;
		}
		len++;
		i++;
	}
	return (++len);
}

char	*ft_trim_spaces(char *s)
{
	size_t	j;
	char	*r;

	r = ft_calloc(ft_one_space_len(s), sizeof(char));
	if (!s || !r)
		return (free(r), NULL);
	j = 0;
	while (ft_isspace(*s))
		s++;
	while (*s)
	{
		while (ft_isspace(*s) && (ft_isspace(*(s + 1)) || !*(s + 1)))
		{
			s++;
			continue ;
		}
		if (ft_isspace(*s))
			r[j++] = 32;
		else
			r[j++] = *s;
		s++;
	}
	return (r);
}

// int	main()
// {
// 	char	*s = "     1 2  3		\n\n4\n5\v\v6\b\t\b7\t\t8 ";
// 	char	*t = "  1 2  ";
// 	char	*r;

// 	printf("total len = %zu\n", ft_one_space_len(t));
// 	r = ft_trim_spaces(s);
// 	printf("r = \"%s\"\n", r);
// }
