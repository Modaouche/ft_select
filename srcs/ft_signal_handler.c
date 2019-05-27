/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/02/02 14:36:26 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

static void			resize(int sig)
{
	(void)sig;
	ioctl(STDERR_FILENO, TIOCSTI, "");
}

static void			susp(int sig)
{
	struct termios	*termiold;
	struct termios	*termios;
	char			cc[2];

	(void)sig;
	if (isatty(STDOUT_FILENO))
	{
		termiold = NULL;
		termios = NULL;
		termiold = ft_term_backup(0);
		termios = ft_term_raw(0);
		cc[0] = termiold->c_cc[VSUSP];
		cc[1] = '\0';
		(tcgetattr(STDERR_FILENO, termios) == -1)\
		? ft_toexit(0, "tcgetattr") : 0;
		(tcsetattr(STDERR_FILENO, TCSADRAIN, termiold) == -1)\
		? ft_toexit(0, "tcsetattr") : 0;
		tputs(tgetstr("ve", NULL), 1, ft_puti);
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDERR_FILENO, TIOCSTI, cc);
	}
}

static void			restart(int sig)
{
	struct termios	*termiold;
	struct termios	*termios;

	(void)sig;
	termiold = NULL;
	termios = NULL;
	termiold = ft_term_backup(0);
	termios = ft_term_raw(0);
	tputs(tgetstr("vi", NULL), 1, ft_puti);
	(tcgetattr(STDERR_FILENO, termiold) == -1) ? ft_toexit(0, "tcgetattr") : 0;
	(tcsetattr(STDERR_FILENO, TCSADRAIN, termios) == -1)\
	? ft_toexit(0, "tcsetattr") : 0;
	signal(SIGTSTP, susp);
	resize(0);
}

static void			end(int sig)
{
	struct termios	*termiold;

	(void)sig;
	termiold = ft_term_backup(0);
	tputs(tgetstr("te", NULL), 1, ft_puti);
	tputs(tgetstr("ve", NULL), 1, ft_puti);
	(tcsetattr(STDERR_FILENO, TCSADRAIN, termiold) == -1)\
	? ft_toexit(0, "tcsetattr") : 0;
	ft_term_backup(1);
	ft_term_raw(1);
	exit(EXIT_SUCCESS);
}

void				ft_signal_handle(void)
{
	signal(SIGINT, end);
	signal(SIGTERM, end);
	signal(SIGQUIT, end);
	signal(SIGTSTP, susp);
	signal(SIGWINCH, resize);
	signal(SIGCONT, restart);
}
