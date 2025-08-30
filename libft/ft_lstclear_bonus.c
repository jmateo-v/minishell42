/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:41:52 by rafael-m          #+#    #+#             */
/*   Updated: 2025/07/20 22:15:35 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
/*
Elimina y libera el nodo ’lst’ dado y todos los consecutivos de ese nodo,
utilizando la función ’del’ y free(3). Al final, el puntero a la lista debe ser
NULL.*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*next_node;

	if (!lst || ! *lst)
		return ;
	node = *lst;
	while (node)
	{
		next_node = node->next;
		if (del)
			del(node->content);
		free (node);
		node = next_node;
	}
	*lst = NULL;
}
/*
int     main(void)
{
	int	lg;
	char *s1 = ft_strdup("Hola");
        t_list  *node1;
	node1 = ft_lstnew(s1);
        char *s2 = ft_strdup("que");
        t_list  *node2;
	node2 = ft_lstnew(s2);
        char *s3 = ft_strdup("tal");
	t_list	*node3;
	node3 = ft_lstnew(s3);
        char *s4 = ft_strdup("Adios");
        t_list  *node4;
	node4 = ft_lstnew(s4);

	ft_lstadd_back(&node1, node2);
	ft_lstadd_back(&node1, node3);
	ft_lstadd_back(&node1, node4);
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
        ft_lstclear(&node1, free);
}*/
