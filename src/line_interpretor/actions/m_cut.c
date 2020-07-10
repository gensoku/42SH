/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_cut.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:02:51 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void			cut_all(t_env *e)
{
	char *tmp;

	if (e->line && e->line[e->cursor->total])
	{
		if (e->cut)
			free(e->cut);
		e->cut = ft_strdup(&e->line[e->cursor->total]);
		e->line[e->cursor->total] = 0;
		tmp = ft_strdup(e->line);
		free(e->line);
		e->line = tmp;
		cursor_set(e, e->cursor, e->line);
		tputs(tgetstr("cd", NULL), 1, spec_put);
	}
}

void					move_cut(t_env *e)
{
	if (e->line && e->line[e->cursor->total])
	{
		if (e->cut)
			free(e->cut);
		e->cut = ft_strdup(&e->line[e->cursor->total]);
		cut_all(e);
		reset_comp(e);
		if (e->color_def & COL_EN)
			checks_syn_col(e, e->line, *e->cursor, 0);
	}
}
