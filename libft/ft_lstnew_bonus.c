/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:05:46 by rafael-m          #+#    #+#             */
/*   Updated: 2025/07/20 22:15:35 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>

Crea un nuevo nodo utilizando malloc(3). La variable miembro ’content’ se
inicializa con el contenido del parámetro ’content’. La variable ’next’,
con NULL.

RETURN
El nuevo nodo.
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	if (!content)
		return (NULL);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/*
int	main(void)
{
//	char	*content = NULL;
	t_list	*new_node;
//	char	*s;

//	printf("content = %p\n", content);
	new_node = ft_lstnew(NULL);
	if (!(new_node->content))
		printf("NULL");
	if (!(new_node->next))
		printf("NULL");
	free (new_node->content);
	free (new_node);
//	s = new_node->content;
//	printf("*s = %s\n", s);
//	printf("s = %p\n", s);
}*/
