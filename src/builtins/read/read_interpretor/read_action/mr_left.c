/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_left.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:03:04 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	r_move_left(t_env *e, int silent)
{
	int	cl;

	if (e->cursor->total > 0)
	{
		if (e->cursor->col == 0 && e->cursor->row != 0 && !silent)
		{
			tputs(tgetstr("up", NULL), 1, spec_put);
			cl = e->col;
			while (cl > 0)
			{
				tputs(tgetstr("nd", NULL), 1, spec_put);
				cl--;
			}
		}
		else if (!silent)
			tputs(tgetstr("le", NULL), 1, spec_put);
		cursor_less(e, 1);
	}
}
