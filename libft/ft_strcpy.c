/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:27:48 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/21 14:37:21 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  strcpy()  function copies the string pointed to by src, including the
 * terminating null byte ('\0'), to the buffer pointed to by dest.  The strings
 * may  not  overlap,  and  the  destination string dest must be large enough
 * to receive the copy.  Beware of buffer overruns! 
 *
 * RETURN VALUE
       Returns a pointer to the destination string dest.*/

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
