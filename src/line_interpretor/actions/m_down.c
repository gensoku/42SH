/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_down.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:02:55 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	move_down(t_env *e)
{
	if (e->tmp_histo && e->tmp_histo->previous)
	{
		e->tmp_histo = e->tmp_histo->previous;
		set_current_histo(e);
	}
	else if (e->prev_histo)
	{
		ft_del_screen(e->line, e->cursor->total, e);
		if (e->line)
			free(e->line);
		e->line = ft_strdup(e->prev_histo);
		ft_putstr(e->line);
		cursor_set(e, e->cursor, e->line);
		e->tmp_histo = NULL;
		if (e->color_def & COL_EN)
			checks_syn_col(e, e->line, *e->cursor, 0);
	}
}
