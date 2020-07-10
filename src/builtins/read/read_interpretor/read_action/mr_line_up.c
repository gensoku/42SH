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

void		r_move_mult_up(t_env *e, int silent)
{
	int cl;

	if (!e->line)
		return ;
	if (e->cursor->total - e->col > 0)
	{
		cl = e->col;
		while (cl)
		{
			r_move_left(e, silent);
			cl--;
		}
	}
	else if (e->cursor->row != 0)
		r_move_home(e, silent);
}
