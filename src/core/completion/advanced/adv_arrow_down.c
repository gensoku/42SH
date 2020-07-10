/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_arrow_down.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:48:41 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	arrow_down_(t_env *e, t_cursor *all)
{
	t_lst_av	*tmp;
	int			z;

	z = 0;
	tmp = e->cur_node;
	tmp->current = 0;
	while (z < all->total)
	{
		z++;
		tmp = tmp->next;
	}
	tmp->current = 1;
	e->cur_node = tmp;
	reset_print(e, all);
}
