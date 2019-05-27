/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_term.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/02 17:25:05 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

struct termios				*ft_term_backup(char bt)
{
	static struct termios	*termiold = NULL;

	if (!termiold)
	{
		if (!(termiold = (struct termios*)malloc(sizeof(struct termios))))
			ft_toexit(0, "Malloc");
		if (tcgetattr(STDIN_FILENO, termiold) == -1)
			ft_toexit(0, "tcgetattr");
		termiold->c_lflag |= (ICANON | ECHO);
		termiold->c_oflag |= (OPOST);
	}
	if (bt == 1)
	{
		if (termiold)
			free(termiold);
		return (0);
	}
	return (termiold);
}

struct termios				*ft_term_raw(char bt)
{
	static struct termios	*termios = NULL;

	if (!termios)
	{
		if (!(termios = (struct termios*)malloc(sizeof(struct termios))))
			ft_toexit(0, "Malloc");
		if (tcgetattr(STDERR_FILENO, termios) == -1)
			ft_toexit(0, "tcgetattr");
		termios->c_lflag &= ~(ICANON | ECHO);
		termios->c_oflag &= ~(OPOST);
		termios->c_cc[VTIME] = 0;
		termios->c_cc[VMIN] = 1;
	}
	if (bt == 1)
	{
		if (termios)
			free(termios);
		termios = NULL;
		return (0);
	}
	return (termios);
}

void						ft_set_term(t_select *select)
{
	tputs(tgetstr("vi", NULL), 1, ft_puti);
	tputs(tgetstr("ti", NULL), 1, ft_puti);
	select->termiold = ft_term_backup(0);
	select->termios = ft_term_raw(0);
	select->begin_list = NULL;
	select->current = NULL;
	select->end_list = NULL;
	select->search = NULL;
	select->max_len = 0;
	select->key = 0;
	if (!(select->wsize = (struct winsize*)malloc(sizeof(struct winsize))))
		ft_toexit(select, "Malloc");
	if (!isatty(STDERR_FILENO))
		ft_toexit(select, "isatty");
	if (tcsetattr(STDERR_FILENO, TCSADRAIN, select->termios) == -1)
		ft_toexit(0, "tcsetattr");
}
