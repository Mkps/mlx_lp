/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloubier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:50:54 by aloubier          #+#    #+#             */
/*   Updated: 2022/11/28 12:54:56 by aloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*last_elem;

	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	last_elem = ft_lstlast(*lst);
	last_elem->next = new_node;
}
