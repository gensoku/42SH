/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_end.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:02:57 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		r_move_end(t_env *e, int silent)
{
	int save;

	if (!e->line)
		return ;
	if (ft_strlen(e->line) >= (size_t)((e->col) * (e->row) -
		get_size_prompt(NULL)) && !silent)
	{
		tputs(tgetstr("cl", NULL), 1, spec_put);
		print_curseur(NULL);
		save = ft_strlen(e->line) - ((e->col) *
				(e->row) - get_size_prompt(NULL)) + e->col - e->cursor->col;
		ft_putstr(&e->line[save]);
	}
	else
	{
		while (e->cursor->total != (int)ft_strlen(e->line))
			r_move_right(e, silent);
	}
}
