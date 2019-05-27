/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 01:04:10 by modaouch          #+#    #+#             */
/*   Updated: 2019/01/21 04:14:23 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			ft_puti(int i)
{
	return (write(STDERR_FILENO, &i, 1));
}

void		ft_w_too_small(void)
{
	ft_putendl_fd("/!\\  Too small  /!\\", STDERR_FILENO);
}
