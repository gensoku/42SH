/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_less.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:01 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			cursor_less(t_env *e, int x)
{
	if (e->cursor->total == 0)
		return ;
	e->cursor->total -= x;
	if (e->cursor->col == 0)
	{
		e->cursor->row--;
		if (e->cursor->row == 0)
			e->cursor->col = e->col - get_size_prompt(NULL) - 1;
		else
			e->cursor->col = e->col - 1;
	}
	else
		e->cursor->col -= x;
}
