/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_tab.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 07:31:06 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:03:18 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		comp_with_p(t_env *e)
{
	if (!e->comp_path)
	{
		searcher(e, 0);
		if (e->comp_screen == 2 && e->comp_exe && e->comp_exe->next)
		{
			e->comp_exe = e->comp_exe->next;
			e->comp_screen = 0;
		}
		print_comp(e);
		display_col(e->comp_path, e);
	}
	else
	{
		if (!e->comp_exe && e->comp_path->next)
		{
			e->comp_screen = 2;
			e->comp_exe = e->comp_path;
		}
		print_comp(e);
		display_col(e->comp_path, e);
	}
}

void			move_tab(t_env *e)
{
	if (loc_var_rep(e, &e->line, 0, 0) || check_history_replace(e, 0))
	{
		move_home(e);
		cursor_set(e, e->cursor, e->line);
		tputs(tgetstr("cd", NULL), 1, spec_put);
		ft_putstr(e->line);
		if (e->color_def & COL_EN)
			checks_syn_col(e, e->line, *e->cursor, 0);
		return ;
	}
	comp_with_p(e);
}
