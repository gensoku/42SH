/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_flag_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:32:57 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	print_jobs_p(t_childs *tmp, t_env *e, int i, int z)
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
		(tmp->child) ? ft_putnbr_fd(tmp->child, 2) : 0;
		ft_putchar_fd('\n', 2);
		i--;
		z++;
	}
}
