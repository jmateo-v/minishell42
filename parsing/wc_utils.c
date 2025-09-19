/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:08:45 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/09/19 10:08:51 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_init_var(size_t *i, size_t *j, size_t *i_a, size_t *j_after)
{
	*i = 0;
	*j = 0;
	*i_a = 0;
	*j_after = 0;
	return (1);
}

int	ft_equal(size_t *j, size_t *i)
{
	*j = *j + 1;
	*i = *i + 1;
	return (1);
}

int	ft_j_s(size_t *j_s, size_t *i_a, size_t *i, size_t *j)
{
	*i_a = *i_a + 1;
	*i = *i_a;
	*j = *j_s;
	return (1);
}