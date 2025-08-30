/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:08:17 by rafael-m          #+#    #+#             */
/*   Updated: 2025/07/20 22:15:35 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

/* Itera la lista ’lst’ y aplica la función ’f’ al contenido de cada
 * nodo. Crea una lista resultante de la aplicación correcta y sucesiva de
 * la función ’f’ sobre cada nodo. La función ’del’ se utiliza para
 * eliminar el contenido de un nodo, si hace falta.

 RETURN
 La nueva lista. NULL si falla la reserva de memoria.
 
static void     *ft_to_uppercase_i(void *s)
{
	char	*original = (char *)s;
	char	*copia = ft_strdup(original);
	if (!copia) return NULL;

	char *d = copia;
	while (*d)
	{
		if (*d >= 'a' && *d <= 'z')
			*d = *d - 32;
		d++;
	}
	return copia;
}
*/
static void	*ft_errors_lst(void *content, t_list **lst, void (*del)(void *))
{
	del(content);
	ft_lstclear(lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_lst;
	void	*trans_content;

	new_lst = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		trans_content = f(lst->content);
		if (!trans_content)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		new_node = ft_lstnew(trans_content);
		if (!new_node)
			return (ft_errors_lst(trans_content, &new_lst, del));
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
/*
int     main(void)
{
//	int	i = 0;
	int	lg;
	t_list	*new_list;
	t_list  *list = NULL;
	char *s1 = ft_strdup("Hola");
        t_list  *node1;
	node1 = ft_lstnew(s1);
        char *s2 = ft_strdup("que");
        t_list  *node2;
	node2 = ft_lstnew(s2);
        char *s3 = NULL;//ft_strdup("tal");
	t_list	*node3;
	node3 = ft_lstnew(s3);
        char *s4 = ft_strdup("adios");
        t_list  *node4;
	node4 = ft_lstnew(s4);

	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node3);
	ft_lstadd_back(&list, node4);
	new_list = ft_lstmap(node1, ft_to_uppercase_i, free);
	if (!new_list)
	{
		ft_lstclear(&node1, free);
		return (1);
	}
	printf("new_list1 = %p\n", new_list);
//	while (new_list)
//	{
//		printf("new_list->content = %s\n", (char *)new_list->content);
//		printf("new_list[%d] = %p\n", i, new_list);
//		printf("new_list[%d]->next = %p\n", i, new_list->next);
//		new_list = new_list->next;
//		i++;
//	}
	lg = ft_lstsize(new_list);
	printf("lg new_list = %d\n", lg);
	ft_lstclear(&list, free);
	ft_lstclear(&new_list, free);
}*/
