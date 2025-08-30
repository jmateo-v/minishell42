/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esc_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:10:20 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/09 19:36:49 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char *s, char *esc_char)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\\' && ft_strchr(esc_char, s[i + 1]))
			i++;
		len++;
		i++;
	}
	return (len);
}

char	*ft_esc_str(char *s, char *esc_char, size_t n)
{
	int		len;
	char	*r;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (n <= 0 || n > ft_strlen(s))
		return (ft_strdup(s));
	len = ft_len(s, esc_char);
	r = (char *)ft_calloc(len + 1, sizeof(char));
	if (!r)
		return (NULL);
	while (i < n)
	{
		if (s[i] == '\\' && ft_strchr(esc_char, s[i]))
			r[j] = s[++i];
		else
			r[j] = s[i];
		i++;
		j++;
	}
	return (r);
}
