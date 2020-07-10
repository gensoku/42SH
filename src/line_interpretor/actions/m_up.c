/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_up.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:03:22 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		m_up_no_histo(t_env *e)
{
	t_cursor	cur_line;

	(e->prev_histo) ? ft_memdel((void**)&(e->prev_histo))
		: (void)e->prev_histo;
	e->prev_histo = (e->line) ? ft_strdup(e->line) :
		ft_strdup("");
	e->tmp_histo = e->histo;
	if (e->tmp_histo && e->tmp_histo->name)
		set_current_histo(e);
	reset_comp(e);
	if (e->color_def & COL_EN)
	{
		cursor_set(e, &cur_line, e->line);
		checks_syn_col(e, e->line, *e->cursor, 0);
		(cur_line.col == 0 && cur_line.row != 0) ? ft_putchar(' ') : 0;
		ft_del_spec_screen(e, 0);
	}
}

void			move_up(t_env *e)
{
	t_cursor	cur_line;

	if (!e->tmp_histo)
		m_up_no_histo(e);
	else if (e->tmp_histo->next)
	{
		e->tmp_histo = e->tmp_histo->next;
		set_current_histo(e);
		reset_comp(e);
		if (e->color_def & COL_EN)
		{
			cursor_set(e, &cur_line, e->line);
			checks_syn_col(e, e->line, *e->cursor, 0);
			(cur_line.col == 0 && cur_line.row != 0) ? ft_putchar(' ') : 0;
			ft_del_spec_screen(e, 0);
		}
	}
}
