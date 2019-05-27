/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 09:00:39 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/02 14:21:05 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	ft_toexit(t_select *select, char *str)
{
	tputs(tgetstr("ve", NULL), 1, ft_puti);
	tputs(tgetstr("te", NULL), 1, ft_puti);
	if (select && select->begin_list)
		ft_dlist_delall(&select->begin_list);
	if (select && select->termiold)
	{
		select->termiold->c_lflag |= (ICANON | ECHO);
		select->termiold->c_oflag |= (OPOST);
		tcsetattr(STDERR_FILENO, TCSAFLUSH, select->termiold);
		free(select->termiold);
	}
	if (select && select->termios)
		free(select->termios);
	if (select && select->wsize)
		free(select->wsize);
	if (select && select->search)
		ft_strdel(&(select->search));
	ft_putstr_fd("./ft_select : ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(" : failed", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
