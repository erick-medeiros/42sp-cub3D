/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:50:47 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/08/10 00:54:06 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdel(t_list **head)
{
	t_list	*node;

	if (!head)
		return (NULL);
	node = *head;
	*head = node->next;
	node->next = NULL;
	return (node);
}
