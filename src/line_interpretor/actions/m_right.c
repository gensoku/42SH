/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_right.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:03:16 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	move_right(t_env *e)
{
	if (e->cursor->total < (int)ft_strlen(e->line)
		&& e->line[e->cursor->total])
	{
		if (e->cursor->col == e->col - 1 || (e->cursor->col
			+ get_size_prompt(NULL) == e->col - 1 && e->cursor->row == 0))
		{
			tputs(tgetstr("do", NULL), 1, spec_put);
			tputs(tgetstr("cr", NULL), 1, spec_put);
		}
		else
			tputs(tgetstr("nd", NULL), 1, spec_put);
		cursor_add(e, 1);
	}
}
