/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 14:15:40 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/21 01:09:52 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void		print_return(t_select *select)
{
	t_dlist	*tmp;

	tmp = select->begin_list;
	while (tmp)
	{
		if (tmp->selected == 1)
		{
			ft_putstr(tmp->name);
			write(STDOUT_FILENO, " ", 1);
		}
		tmp = tmp->next;
	}
	key_quit(select, 0);
}

void		ft_print_select(char *str, char *name, int selected, int is_cur)
{
	char	*color_cap;
	char	*reset;
	int		len;

	len = ft_strlen(name);
	if (is_cur)
		ft_underlined_cursor(1);
	if (!selected)
		return (ft_putstr_fd(ft_memcpy(str, name, len), STDERR_FILENO));
	reset = tgetstr("me", NULL);
	color_cap = tgetstr("AB", NULL);
	(is_cur) ? tputs(tparm(color_cap, COLOR_GREEN), 1, ft_puti)\
		: tputs(tparm(color_cap, COLOR_WHITE), 1, ft_puti);
	color_cap = tgetstr("AF", NULL);
	(is_cur) ? tputs(tparm(color_cap, COLOR_WHITE), 1, ft_puti)\
		: tputs(tparm(color_cap, COLOR_BLACK), 1, ft_puti);
	ft_putstr_fd(ft_memcpy(str, name, len), STDERR_FILENO);
	tputs(reset, 1, ft_puti);
}

void		ft_print_search(t_select *select)
{
	ft_putendl_fd("\n\n", STDERR_FILENO);
	tputs(tgetstr("cr", NULL), 1, ft_puti);
	ft_putstr_fd("Search : ", STDERR_FILENO);
	ft_putstr_fd(select->search, STDERR_FILENO);
}

static void	ft_init_new_line(int *count)
{
	*count = 0;
	ft_putendl_fd("", STDERR_FILENO);
	tputs(tgetstr("cr", NULL), 1, ft_puti);
}

void		ft_print_dlist(t_select *select)
{
	t_dlist	*dlist;
	int		limits_col;
	int		count;
	char	*str;

	count = 0;
	dlist = select->begin_list;
	tputs(tgetstr("cl", NULL), 1, ft_puti);
	if ((limits_col = ft_get_limits_col(select)) == -1)
		return (ft_w_too_small());
	if (!(str = ft_strnew(select->max_len + 1)))
		ft_toexit(select, "Malloc");
	while (dlist)
	{
		ft_memset(str, ' ', select->max_len + 1);
		ft_print_select(str, dlist->name, dlist->selected,\
				(dlist == select->current));
		ft_underlined_cursor(0);
		if (++count >= limits_col)
			ft_init_new_line(&count);
		dlist = dlist->next;
	}
	if (select->search)
		ft_print_search(select);
	ft_strdel(&str);
}
