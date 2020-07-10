/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_select_cur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:48:59 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		select_cur(t_env *e, t_cursor *all)
{
	if (e->cur_node)
	{
		if (e->cur_node->selected == 0)
		{
			e->cur_node->selected = 1;
			arrow_right_(e, all);
		}
		else
			e->cur_node->selected = 0;
	}
	reset_print(e, all);
}
