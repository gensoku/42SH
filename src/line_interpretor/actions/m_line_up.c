/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_line_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:03:07 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		move_mult_up(t_env *e)
{
	int cl;

	if (!e->line)
		return ;
	if (e->cursor->total - e->col > 0)
	{
		cl = e->col;
		while (cl)
		{
			move_left(e);
			cl--;
		}
	}
	else if (e->cursor->row != 0)
		move_home(e);
}
