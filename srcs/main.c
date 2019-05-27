/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/02 14:45:22 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static int		ft_init_term(int ac)
{
	char		*term_type;
	int			ret;

	if (ac < 2)
	{
		ft_putendl_fd("usage: ./ft_select [ARG1] [ARG2] ...", STDERR_FILENO);
		return (-1);
	}
	if (!(term_type = getenv("TERM")))
	{
		ft_putendl_fd("TERM must be set (see environement handling command)",\
			STDERR_FILENO);
		return (-1);
	}
	ret = tgetent(NULL, getenv("TERM"));
	if (ret == 1 && ft_strcmp("dumb", getenv("TERM")))
		return (0);
	(ret > 0 && ft_strcmp("dumb", getenv("TERM")))\
		? ft_putendl_fd("./ft_select : DataBase is unaccessible : quit",\
		STDERR_FILENO)\
		: ft_putendl_fd("./ft_select : too few information in DataBase : quit",\
		STDERR_FILENO);
	return (-1);
}

int				main(int ac, char **av)
{
	t_select	select;

	if (ft_init_term(ac) == -1)
		return (1);
	ft_set_term(&select);
	ft_signal_handle();
	ft_dlist_handle(&select, av);
	ft_select(&select);
	return (0);
}
