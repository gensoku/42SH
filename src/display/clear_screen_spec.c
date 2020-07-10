/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_screen_spec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/16 05:12:57 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void	move_static_test(int rw, int cl, int col2)
{
	tputs(tgetstr("cr", NULL), 1, spec_put);
	if (rw == 0)
	{
		cl = get_size_prompt(NULL);
		while (cl > 0)
		{
			tputs(tgetstr("nd", NULL), 1, spec_put);
			cl--;
		}
	}
	cl = col2;
	while (cl > 0)
	{
		tputs(tgetstr("nd", NULL), 1, spec_put);
		cl--;
	}
}

void		ft_del_spec_screen_lined(t_env *e, int flag, t_cursor *ref)
{
	int			rw;
	t_cursor	cur;

	cursor_set(e, &cur, e->line);
	rw = ref->row;
	if (cur.col == 0 && flag != 1)
		cur.row--;
	if (cur.row != rw)
	{
		while (rw < cur.row)
		{
			tputs(tgetstr("up", NULL), 1, spec_put);
			rw++;
		}
	}
	move_static_test(ref->row, 0, ref->col);
}

void		ft_del_spec_screen(t_env *e, int flag)
{
	int			rw;
	t_cursor	cur;

	cursor_set(e, &cur, e->line);
	rw = e->cursor->row;
	if (cur.col == 0 && flag != 1)
		cur.row--;
	if (cur.row != rw)
	{
		while (rw < cur.row)
		{
			tputs(tgetstr("up", NULL), 1, spec_put);
			rw++;
		}
	}
	move_static_test(e->cursor->row, 0, e->cursor->col);
}
