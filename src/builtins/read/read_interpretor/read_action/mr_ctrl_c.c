/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_ctrl_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:02:47 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int		r_move_ctrl_c(t_env *e)
{
	if (e->save_quote)
		free(e->save_quote);
	tputs(tgetstr("cd", NULL), 1, spec_put);
	e->save_quote = NULL;
	e->flag = 0;
	e->count_qu->pr = 0;
	e->count_qu->bq = 0;
	e->count_qu->ac = 0;
	e->comp_screen = 0;
	if (e->line)
		free(e->line);
	e->line = NULL;
	cursor_reset(e);
	e->tmp_histo = NULL;
	reset_comp(e);
	return (1);
}
