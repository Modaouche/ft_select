/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 02:48:42 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/21 03:20:38 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void		ft_dlist_handle(t_select *select, char **av)
{
	int		i;

	i = 1;
	select->max_len = ft_get_biggest_len(av);
	while (av[i])
	{
		ft_dlist_add(select, av[i]);
		i++;
	}
	select->current = select->begin_list;
}

void		get_and_dump_key(t_select *select, char *buff)
{
	unsigned int		key_ref;
	unsigned int		n;
	static t_key_code	keytab[] = {
		{S_KEY_ARW_LEFT, &key_arrow}, {S_KEY_ARW_RIGHT, &key_arrow},
		{S_KEY_ARW_BOT, &key_arrow}, {S_KEY_ARW_TOP, &key_arrow},
		{S_KEY_ERASE, &key_erase}, {S_KEY_ESC, &key_quit},
		{S_KEY_RET, &key_return}, {S_KEY_CTRL_D, &key_quit},
		{S_KEY_SPACE, &key_space}, {S_KEY_SEARCH, &key_search},
		{S_KEY_NONE, NULL}
	};

	key_ref = buff[0] + (buff[1] * 256) + (buff[2] * 256 * 256);
	if (key_ref >= 33 && key_ref <= 126)
		key_ref = 82;
	n = 0;
	while (keytab[n].key)
	{
		if (keytab[n].key == key_ref)
		{
			keytab[n].dump_key(select, buff);
			break ;
		}
		n++;
	}
}

void		liberation(t_select *select)
{
	tputs(tgetstr("te", NULL), 1, ft_puti);
	tputs(tgetstr("ve", NULL), 1, ft_puti);
	if (tcsetattr(STDERR_FILENO, TCSADRAIN, select->termiold) == -1)
		ft_toexit(0, "tcsetattr");
	if (select->key == S_KEY_RET)
		print_return(select);
	ft_term_backup(1);
	ft_term_raw(1);
	if (select->wsize)
		free(select->wsize);
	if (select->search)
		free(select->search);
}

void		ft_select(t_select *select)
{
	char	buff[MAX_KEY_LEN + 1];
	int		ret;

	while (42)
	{
		ft_print_dlist(select);
		ft_bzero(buff, MAX_KEY_LEN + 1);
		ret = read(STDIN_FILENO, buff, MAX_KEY_LEN);
		if (ret <= LIMIT_KEY)
		{
			get_and_dump_key(select, buff);
			if (select->key == S_KEY_END || select->key == S_KEY_RET)
				break ;
		}
	}
	liberation(select);
}
