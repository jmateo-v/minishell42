/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:26:29 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/16 16:16:08 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <ctype.h>

 checks for an alphabetic character;
 * in the standard "C" locale, it is equivalent to (isup‐
              per(c)  ||  islower(c)).   In  some  locales,
	      there may be additional characters for which
              isalpha() is true—letters which are neither
	      uppercase nor lowercase.
 */

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1024);
	return (0);
}
/*
int	main(void)
{
	int	*c = 123;

	printf("%lu\n", c);
	printf("%p\n", c);
//	printf("ft = %d\n", ft_isalpha(*c));
//	printf("s = %d\n", isalpha(*c));
}*/
