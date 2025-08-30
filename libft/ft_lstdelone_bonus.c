/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:42:13 by rafael-m          #+#    #+#             */
/*   Updated: 2025/07/20 22:15:35 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>
#include <stdio.h
 * Toma como parámetro un nodo ’lst’ y libera la memoria del contenido
 * utilizando la función ’del’ dada como parámetro, además de liberar el nodo.
 * La memoria de ’next’ no debe liberarse. */

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free (lst);
}
/*
int	main(void)
{
	char *s = strdup("Hola");
	t_list	*nodo;

	nodo = ft_lstnew(s);
	ft_lstdelone(nodo, free);
}*/
