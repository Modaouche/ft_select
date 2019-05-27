/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 08:29:54 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/02 11:14:42 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int				ft_get_biggest_len(char **av)
{
	int			biggest;
	int			cmp;
	int			i;

	i = 1;
	biggest = 0;
	while (av[i])
	{
		cmp = ft_strlen(av[i]);
		if (cmp > biggest)
			biggest = cmp;
		i++;
	}
	return (biggest);
}

void			ft_underlined_cursor(int bt)
{
	char		*color_cap;

	if (bt == 1)
	{
		tputs(tgetstr("me", NULL), 1, ft_puti);
		color_cap = tgetstr("AF", NULL);
		tputs(tparm(color_cap, COLOR_GREEN), 1, ft_puti);
		tputs(tgetstr("us", NULL), 1, ft_puti);
		tputs(tgetstr("md", NULL), 1, ft_puti);
	}
	else
		tputs(tgetstr("me", NULL), 1, ft_puti);
}

int				ft_parse_column_row(int nb, t_select *select)
{
	if ((ft_dlist_len(select->begin_list) / nb) >= select->wsize->ws_row || !nb)
		return (-1);
	if (select->max_len + 1 >= select->wsize->ws_col)
		return (-1);
	return (0);
}

int				ft_get_limits_col(t_select *select)
{
	t_dlist		*tmp;
	int			limits_col;
	int			w_col;
	int			nb;

	nb = 0;
	tmp = select->begin_list;
	limits_col = select->max_len + 1;
	ioctl(STDERR_FILENO, TIOCGWINSZ, select->wsize);
	w_col = select->wsize->ws_col;
	while (tmp)
	{
		nb++;
		limits_col += select->max_len + 1;
		if (limits_col >= w_col || nb >= 14)
			break ;
		tmp = tmp->next;
	}
	if (ft_parse_column_row(nb, select) == -1)
		return (-1);
	return (nb);
}
