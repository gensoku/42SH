/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_ctrl_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:02:50 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	move_ctrl_l(t_env *e)
{
	move_ctrl_c(e);
	if (e->line)
		free(e->line);
	e->line = NULL;
	cursor_reset(e);
	e->tmp_histo = NULL;
	reset_comp(e);
	tputs(tgetstr("cl", NULL), 1, spec_put);
	print_curseur(NULL);
}
