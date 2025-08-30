/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:16:12 by rafael-m          #+#    #+#             */
/*   Updated: 2025/07/20 22:15:35 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Devuelve el último nodo de la lista. */

#include "libft.h"

//#include <stdio.h>

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
/*
int	main(void)
{
	t_list	*last;
	t_list	*first_node = NULL;
	t_list	*node1 = ft_lstnew("Hola");
        t_list	*node2 = ft_lstnew("que");
	t_list	*node3 = ft_lstnew("tal");
	t_list	*node4 = ft_lstnew("Adios");

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
	last = ft_lstlast(node1);
	printf("last = %p\n", last);
}*/
