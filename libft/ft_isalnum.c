/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:24:45 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/16 16:17:01 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdio.h>
#include <ctype.h>

 checks for an alphanumeric character;
 * it is equivalent to (isalpha(c) || isdigit(c)). */

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (8);
	return (0);
}
/*
int	main(void)
{
	char	c = 123214134140;

	printf("ft = %d\n", ft_isalnum(c));
	printf("s = %d\n", isalnum(c));
	printf("%c\n", c);
}*/
