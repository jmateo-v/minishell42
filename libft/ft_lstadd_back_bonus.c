/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:31:56 by rafael-m          #+#    #+#             */
/*   Updated: 2025/07/20 22:15:35 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* lst: el puntero al primer nodo de una lista.
new: el puntero a un nodo que añadir a la lista.
Añade el nodo ’new’ al final de la lista ’lst’.
*/
//#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}
/*
int	main(void)
{
	int	lg;
	t_list	**list = NULL;
	t_list	*last_node = ft_lstnew("LAST");
	t_list *node1 = ft_lstnew("Hola");
        t_list *node2 = ft_lstnew("que");
	t_list *node3 = ft_lstnew("tal");
	t_list *node4 = ft_lstnew("adios");

	ft_lstadd_back(list, node2);
	ft_lstadd_back(&node2, node3);
	ft_lstadd_back(&node3, node4);
	ft_lstadd_back(&node4, last_node);
	ft_lstadd_back(&node1, last_node);
	printf("last_node = %p\n", last_node);
	printf("node1 = %p\n", node1);
	printf("node2 = %p\n", node2);
	printf("node3 = %p\n", node3);
	printf("node4 = %p\n", node4);
	printf("next1 = %p\n", node1->next);
	printf("next2 = %p\n", node2->next);
	printf("next3 = %p\n", node3->next);
	printf("next4 = %p\n", node4->next);
	printf("next5 = %p\n", last_node->next);
	lg = ft_lstsize(node1);
	printf("lg = %d\n", lg);
	ft_lstclear(&node1, free);
}*/
