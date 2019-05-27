/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 03:03:51 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/21 01:32:09 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void			key_arrow(t_select *select, char *buff)
{
	if ((ft_get_limits_col(select)) == -1)
		return (ft_w_too_small());
	if (buff[2] == 65)
		ft_dlist_move_at(select, ft_get_limits_col(select), 0);
	else if (buff[2] == 66)
		ft_dlist_move_at(select, ft_get_limits_col(select), 1);
	else if (buff[2] == 67)
		ft_dlist_move_at(select, 1, 1);
	else if (buff[2] == 68)
		ft_dlist_move_at(select, 1, 0);
}

void			key_space(t_select *select, char *buff)
{
	if (select->search)
		ft_strdel(&(select->search));
	if ((ft_get_limits_col(select)) == -1)
		return (ft_w_too_small());
	select->current->selected = (!select->current->selected) ? 1 : 0;
	if (select->current->selected)
	{
		buff[2] = 67;
		key_arrow(select, buff);
	}
}

void			key_search(t_select *select, char *buff)
{
	t_dlist *tmp;

	tmp = select->begin_list;
	if (!select->search)
		select->search = ft_strnew(select->max_len);
	(ft_strlen(select->search) < select->max_len)\
		? ft_strcat(select->search, buff)\
		: ft_strdel(&(select->search));
	while (tmp && select->search && *(select->search))
	{
		if (!ft_strncmp(tmp->name, select->search, ft_strlen(select->search)))
		{
			select->current = tmp;
			break ;
		}
		tmp = tmp->next;
	}
}
