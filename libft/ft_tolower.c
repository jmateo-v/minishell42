/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:13:34 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/16 17:38:25 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <ctype.h>

If c is an uppercase letter, tolower() returns its lowercase equivalent, if a
lowercase representation exists in the current locale.  Otherwise, it returns
c.
*/

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
/*
int	main(void)
{
	char	c = 'w';

	printf("ft = %c\n", ft_tolower(c));
	printf("s = %c\n", tolower(c));
}*/
