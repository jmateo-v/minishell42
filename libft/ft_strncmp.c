/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:57:43 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/04 12:22:14 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <string.h>
#include <stdio.h>

The  strcmp()  function compares the two strings s1 and s2.  The locale is not
taken into account (for a locale-aware comparison, see strcoll(3)).  The
comparison is done using  unsigned  characters.

strcmp() returns an integer indicating the result of the comparison, as
follows:

       • 0, if the s1 and s2 are equal;

       • a negative value if s1 is less than s2;

       • a positive value if s1 is greater than s2.

The  strncmp() function is similar, except it compares only the first (at most)
n bytes of s1 and s2.

RETURN VALUE
The strcmp() and strncmp() functions return an integer less than, equal to, or
greater than  zero if  s1  (or  the  first n bytes thereof) is found,
respectively, to be less than, to match, or be greater than s2.
*/

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	if (!s1 || !s2 || n <= 0)
		return (-1);
	while (n > 0 && *s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char )*s1 - (unsigned char )*s2);
}
/*
int	main(void)
{
	char	*s1 = "asde";
	char	*s2 = "asd";
	int	result;
	int	n = 10;

	result = ft_strncmp(s1, s2, n);
	printf("result = %d\n", result);
	result = strncmp(s1, s2, n);
	printf("result = %d\n", result);
}
*/
