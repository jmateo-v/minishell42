/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:34:44 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/04 11:56:23 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>
//#include <stdio.h>

static char	*ft_sep_lines(char *str, int depth, char charset)
{
	int	count;
	int	i;
	int	start;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == charset)
			i++;
		if (!str[i])
			break ;
		if (count == depth)
		{
			start = i;
			while (str[i] && str[i] != charset)
				i++;
			return (ft_substr(str, start, i - start));
		}
		while (str[i] && str[i] != charset)
			i++;
		count++;
	}
	return (NULL);
}

static int	ft_depth(char *str, char charset)
{
	int	depth;
	int	word;

	depth = 0;
	word = 0;
	while (*str)
	{
		if (*str != charset && !word)
		{
			depth++;
			word = 1;
		}
		if (*str == charset)
			word = 0;
		str++;
	}
	return (depth);
}

char	**ft_split(char *str, char charset)
{
	char	**result;
	int		depth;
	int		i;

	i = 0;
	if (!str || !charset)
		return (NULL);
	depth = ft_depth(str, charset);
	result = (char **)malloc((depth + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < depth)
	{
		result[i] = ft_sep_lines(str, i, charset);
		if (!result[i])
		{
			while (i-- > 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[depth] = NULL;
	return (result);
}
/*
int	main(void)
{
	int	i = 0;
	char	**result = ft_split("   lorem   ipsum Suspendisse   ", ' ');

	if (!result)
		return (1);
	while (result[i])
	{
		printf("result[%d] = %s\n", i, result[i]);
		i++;
	}
	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
//	printf("depth = %d\n", depth);
	free (result[i]);
	free(result);
	return (0);
}*/
