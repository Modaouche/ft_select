/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 08:38:02 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/02 17:29:22 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

t_dlist			*ft_dlist_new(char *name)
{
	t_dlist		*new_list;

	if (!(new_list = (t_dlist*)malloc(sizeof(t_dlist))))
		return (0);
	if (!(new_list->name = ft_strdup(name)))
	{
		free(new_list);
		return (0);
	}
	new_list->selected = 0;
	new_list->prev = NULL;
	new_list->next = NULL;
	return (new_list);
}

void			ft_dlist_add(t_select *select, char *name)
{
	t_dlist		*tmp;

	if (!(tmp = ft_dlist_new(name)))
		ft_toexit(select, "Malloc");
	if (select->begin_list == NULL)
	{
		select->begin_list = tmp;
		select->end_list = tmp;
		return ;
	}
	tmp->prev = select->end_list;
	select->end_list->next = tmp;
	select->end_list = tmp;
}

int				ft_dlist_len(t_dlist *dlist)
{
	int			i;

	i = 0;
	while (dlist)
	{
		i++;
		dlist = dlist->next;
	}
	return (i);
}
