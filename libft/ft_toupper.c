/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:53:43 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/16 17:36:37 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include <stdio.h>
#include <ctype.h>

If c is a lowercase letter, toupper() returns its uppercase equivalent, if an
uppercase representation exists in the current locale.  Otherwise, it returns
c.
 
       RETURN VALUE
The value returned is that of the converted letter, or c if the conversion was
not possible.
*/
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}
/*
int	main(void)
{
	char	c = 'c';

	printf("ft = %c\n", ft_toupper(c));
	printf("s = %c\n", toupper(c));
}*/
