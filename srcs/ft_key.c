/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 23:58:28 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/21 01:31:14 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void		delete_char_search(t_select *select)
{
	int			i;

	i = ft_strlen(select->search) - 1;
	(i) ? select->search[i] = '\0' : ft_strdel(&(select->search));
}

void			key_erase(t_select *select, char *buff)
{
	(void)buff;
	if (select->search)
		return (delete_char_search(select));
	if ((ft_get_limits_col(select)) == -1)
		return (ft_w_too_small());
	if (select->current == select->begin_list && select->begin_list)
		select->begin_list = select->begin_list->next;
	if (select->current == select->end_list && select->end_list)
		select->end_list = select->end_list->prev;
	ft_dlist_delone(&(select->current));
	if (!select->begin_list || !select->end_list)
	{
		select->end_list = NULL;
		select->begin_list = NULL;
		key_quit(select, 0);
	}
	else if (select->current->next && select->current != select->begin_list)
		select->current = select->current->next;
}

void			key_return(t_select *select, char *buff)
{
	(void)buff;
	select->key = S_KEY_RET;
}

void			key_quit(t_select *select, char *buff)
{
	(void)buff;
	ft_dlist_delall(&(select->begin_list));
	if (!select->end_list)
		select->begin_list = NULL;
	select->key = S_KEY_END;
}
