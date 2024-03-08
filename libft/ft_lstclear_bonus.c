/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:50:23 by pevieira          #+#    #+#             */
/*   Updated: 2023/05/08 14:50:27 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*nextlst;
	t_list	*current;

	if (lst != NULL && del != NULL)
	{
		current = *lst;
		while (current != NULL)
		{
			nextlst = current->next;
			del(current->content);
			free(current);
			current = nextlst;
		}
		*lst = NULL;
	}
}
