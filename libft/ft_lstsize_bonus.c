/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:16:11 by rafael-m          #+#    #+#             */
/*   Updated: 2025/07/20 22:15:35 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>

Cuenta el número de nodos de una lista.*/

int	ft_lstsize(t_list *lst)
{
	if (lst == NULL)
		return (0);
	return (1 + ft_lstsize(lst->next));
}
/*
int	main(void)
{
	int	lg;
	t_list	*first_node = NULL;
	t_list *node1 = ft_lstnew("Hola");
        t_list *node2 = ft_lstnew("que");
	t_list *node3 = ft_lstnew("tal");
	t_list *node4 = ft_lstnew("Adios");

	ft_lstadd_front(&first_node, node4);
	ft_lstadd_front(&first_node, node3);
	ft_lstadd_front(&first_node, node2);
	ft_lstadd_front(&first_node, node1);
	printf("node1 = %p\n", node1);
	printf("node2 = %p\n", node2);
	printf("node3 = %p\n", node3);
	printf("node4 = %p\n", node4);
	printf("next1 = %p\n", node1->next);
	printf("next2 = %p\n", node2->next);
	printf("next3 = %p\n", node3->next);
	printf("next4 = %p\n", node4->next);
	lg = ft_lstsize(node1);
	printf("lg = %d\n", lg);
}*/
