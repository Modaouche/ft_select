/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:49:25 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/21 04:24:52 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H

# define FT_SELECT_H

# include "../libft/libft.h"
# include "../libft/ft_printf/includes/ft_printf.h"
# include <sys/types.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <term.h>
# include <curses.h>
# include <unistd.h>

# define MAX_KEY_LEN		9
# define LIMIT_KEY			3

# define S_KEY_ARW_LEFT		4479771
# define S_KEY_ARW_RIGHT	4414235
# define S_KEY_ARW_BOT		4348699
# define S_KEY_ARW_TOP		4283163
# define S_KEY_ERASE		127
# define S_KEY_SEARCH		82
# define S_KEY_SPACE		32
# define S_KEY_ESC			27
# define S_KEY_RET			10
# define S_KEY_CTRL_D		4
# define S_KEY_END			1
# define S_KEY_NONE			0

typedef struct			s_dlist
{
	struct s_dlist		*prev;
	struct s_dlist		*next;
	char				*name;
	char				selected;
}						t_dlist;

typedef struct			s_select
{
	struct termios		*termiold;
	struct termios		*termios;
	struct winsize		*wsize;
	t_dlist				*begin_list;
	t_dlist				*current;
	t_dlist				*end_list;
	char				*search;
	unsigned int		max_len;
	unsigned int		key;
}						t_select;

typedef struct			s_key_code
{
	unsigned int		key;
	void				(*dump_key)(t_select *select, char *buff);
}						t_key_code;

/*
** Initialization & Co
*/

void					liberation(t_select *select);
struct termios			*ft_term_backup(char bt);
struct termios			*ft_term_raw(char bt);
void					ft_set_term(t_select *select);
void					ft_signal_handle(void);
void					ft_toexit(t_select *select, char *str);
int						ft_get_biggest_len(char **av);
int						ft_open_term(void);
void					ft_underlined_cursor(int bt);
int						ft_get_limits_col(t_select *select);
int						ft_parse_column_row(int nb, t_select *select);

/*
** Selecting:
*/

void					ft_select(t_select *select);
void					get_and_dump_key(t_select *select, char *buff);
void					key_arrow(t_select *select, char *buff);
void					key_erase(t_select *select, char *buff);
void					key_return(t_select *select, char *buff);
void					key_space(t_select *select, char *buff);
void					key_quit(t_select *select, char *buff);
void					key_search(t_select *select, char *buff);

/*
** list:
*/

t_dlist					*ft_dlist_new(char *name);
void					ft_dlist_add(t_select *select, char *name);
void					ft_dlist_delone(t_dlist **dlist);
void					ft_dlist_delall(t_dlist **dlist);
void					ft_dlist_handle(t_select *select, char **av);
void					ft_dlist_move_at(t_select *select,\
						int nb_col, int direction);
int						ft_dlist_len(t_dlist *dlist);

/*
** print :
*/

int						ft_puti(int i);
void					ft_usage(int ac);
void					ft_print_dlist(t_select *select);
void					ft_print_select(char *str, char *dlist, int selected,\
						int is_cur);
void					print_return(t_select *select);
void					ft_w_too_small(void);

#endif
