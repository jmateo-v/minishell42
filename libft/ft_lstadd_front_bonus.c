/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:08:38 by rafael-m          #+#    #+#             */
/*   Updated: 2025/07/20 22:15:35 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdio.h>
#include <stdlib.h>
 lst: la dirección de un puntero al primer nodo de una lista.
new: un puntero al nodo que añadir al principio de la lista. 
Añade el nodo ’new’ al principio de la lista ’lst’.
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
int	main(void)
{
	t_list	*first_node = NULL;
	t_list *node1 = ft_lstnew("Hola");
	t_list *node2 = ft_lstnew("Adios");

	printf("&first_node = %p\n", (void *)first_node);
    printf("node1 = %p\n", (void *)node1);
    printf("node2 = %p\n", (void *)node2);

	ft_lstadd_front(&first_node, node1);
	printf("first_node = %p\n", (void *)first_node);
    printf("node1 = %p\n", (void *)node1);
    printf("node2 = %p\n", (void *)node2);

	ft_lstadd_front(&first_node, node2);
	printf("first_node = %p\n", (void *)first_node);
    printf("node1 = %p\n", (void *)node1);
    printf("node2 = %p\n", (void *)node2);

}*/
