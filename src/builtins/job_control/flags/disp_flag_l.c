/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_flag_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:32:54 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	print_jobs_l(t_childs *tmp, t_env *e, int i, int z)
{
	int y;

	while (i > 0)
	{
		y = i;
		tmp = e->childs;
		while (y - 1)
		{
			tmp = tmp->next;
			y--;
		}
		ft_print_jobs(z);
		ft_print_last_blast(tmp->last);
		ft_putnbr_fd(tmp->child, 2);
		ft_putchar_fd(' ', 2);
		if (tmp->status == 18)
			ft_putstr_fd("Suspended: 18			", 2);
		else if (tmp->status == 22)
			ft_putstr_fd("Stopped (tty output): ", 2);
		else if (tmp->status == 23)
			ft_putstr_fd("Stopped (tty intput): ", 2);
		(tmp->name) ? ft_putendl_fd(tmp->name, 2) : 0;
		i--;
		z++;
	}
}
