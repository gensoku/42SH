/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_line_do.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:03:06 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		move_mult_do(t_env *e)
{
	int			cl;
	t_cursor	cur;

	if (!e->line)
		return ;
	cursor_set(e, &cur, e->line);
	if (e->cursor->total + e->col < (int)ft_strlen(e->line))
	{
		cl = e->col;
		while (cl)
		{
			move_right(e);
			cl--;
		}
	}
	else if (e->cursor->row < cur.row)
		move_end(e);
}
