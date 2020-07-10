/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_no_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:32:59 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	print_jobs_(t_childs *tmp, t_env *e, int i, int z)
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
		ft_print_jobs(tmp->id);
		ft_print_last_blast(tmp->last);
		ft_putstr_fd("Stopped: 					", WCH_FD);
		(tmp->name) ? ft_putendl_fd(tmp->name, 2) : 0;
		i--;
		z++;
	}
}
