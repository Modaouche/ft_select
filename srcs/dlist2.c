/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 01:10:44 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/21 01:29:11 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void		ft_tofree(t_dlist **dlist)
{
	t_dlist		*tmp;

	if (!*dlist)
		return ;
	tmp = *dlist;
	ft_strdel(&(tmp->name));
	free(tmp);
}

void			ft_dlist_delone(t_dlist **dlist)
{
	t_dlist		*tmp;
	t_dlist		*save;

	tmp = *dlist;
	if (!dlist || !tmp)
		return ;
	if (!tmp->next)
	{
		*dlist = ((*dlist)->prev) ? (*dlist)->prev : NULL;
		(*dlist) ? (*dlist)->next = NULL : 0;
		return (ft_tofree(&(tmp)));
	}
	else if (tmp->prev)
	{
		tmp = tmp->prev;
		save = (*dlist)->next;
		ft_tofree(&tmp->next);
		tmp->next = save;
		(save) ? save->prev = tmp : 0;
		*dlist = tmp;
		return ;
	}
	*dlist = (*dlist)->next;
	(*dlist)->prev = NULL;
	ft_tofree(&tmp);
}

void			ft_dlist_delall(t_dlist **dlist)
{
	t_dlist		*tmp;

	tmp = *dlist;
	if (!dlist || !*dlist)
		return ;
	while (tmp)
		ft_dlist_delone(&tmp);
}

int				ft_stop_verticaly(t_select *select, int nb_col, int direction)
{
	t_dlist		*tmp;
	int			new_nb_col;
	int			nb_tmp;

	new_nb_col = 0;
	nb_tmp = nb_col;
	tmp = select->current;
	while (tmp && nb_tmp > 0)
	{
		if (direction == 1)
			tmp = tmp->next;
		else
			tmp = tmp->prev;
		nb_tmp--;
		new_nb_col++;
	}
	if (tmp)
		return (nb_col);
	return (0);
}

void			ft_dlist_move_at(t_select *select, int nb_col, int direction)
{
	if (nb_col > 1)
		nb_col = ft_stop_verticaly(select, nb_col, direction);
	if (direction == 1)
	{
		while (nb_col > 0)
		{
			if (select->current->next)
				select->current = select->current->next;
			else
				select->current = select->begin_list;
			nb_col--;
		}
	}
	else
	{
		while (nb_col > 0)
		{
			if (select->current->prev)
				select->current = select->current->prev;
			else
				select->current = select->end_list;
			nb_col--;
		}
	}
}
