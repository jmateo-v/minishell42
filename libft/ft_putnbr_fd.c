/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:09:36 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/19 16:15:24 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_putnbr_fd(int n, int fd)
{
	int	nbr;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
	}
	nbr = n;
	if (nbr > 9)
		ft_putnbr_fd(n / 10, fd);
	nbr = (n % 10) + 48;
	write (fd, &nbr, 1);
}
/*
int	main(void)
{
	int	fd = 2;

	ft_putnbr_fd(-12312, fd);
	write (1, "\n", 1);
}
*/
