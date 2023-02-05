/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:44:54 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/08/10 00:50:14 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list **head)
{
	t_list	*last;
	t_list	*node;

	if (!head)
		return (NULL);
	node = *head;
	last = ft_lstlast(node);
	while (node->next->next)
		node = node->next;
	node->next = NULL;
	return (last);
}
