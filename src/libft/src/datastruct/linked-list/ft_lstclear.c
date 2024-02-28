/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:32:29 by jolecomt          #+#    #+#             */
/*   Updated: 2024/02/28 14:32:30 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp1;
	t_list	*temp2;

	if (*lst)
	{
		temp1 = *lst;
		while (temp1->next != NULL)
		{
			temp2 = temp1->next;
			ft_lstdelone(temp1, del);
			temp1 = temp2;
		}
		ft_lstdelone(temp1, del);
	}
	*lst = NULL;
}
