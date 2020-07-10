/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_add.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:57:59 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			cursor_add(t_env *e, int x)
{
	if (e->cursor->row == 0)
	{
		if (e->cursor->col + get_size_prompt(NULL) >= e->col - 1)
		{
			e->cursor->col = 0;
			e->cursor->row++;
		}
		else
			e->cursor->col += x;
	}
	else
	{
		if (e->cursor->col >= e->col - 1)
		{
			e->cursor->col = 0;
			e->cursor->row++;
		}
		else
			e->cursor->col += x;
	}
	e->cursor->total += x;
}
