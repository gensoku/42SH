/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_prev_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:03:14 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int		loop_norm_prevw(t_env *e, int cpt, int cur, int opt)
{
	if (opt == 0)
	{
		while (cur - cpt > 0 && e->line[cur - cpt] &&
				!ft_isalnum(e->line[cur - cpt]))
			cpt++;
	}
	else if (opt == 1)
	{
		while (cur - cpt > 0 && e->line[cur - cpt] &&
				ft_isalnum(e->line[cur - cpt]))
		{
			if (e->line[cur - (cpt + 1)] &&
				!ft_isalnum(e->line[cur - (cpt + 1)]))
				break ;
			cpt++;
		}
	}
	else if (opt == 2)
	{
		while (cur - cpt > 0 && e->line[cur - cpt] &&
			ft_isalnum(e->line[cur - cpt]))
			cpt++;
	}
	return (cpt);
}

void			move_previous_word(t_env *e)
{
	int cpt;
	int cur;

	cpt = 0;
	cur = e->cursor->total;
	if (!e->line)
		return ;
	if (cur > 0)
		cpt++;
	else
		return ;
	if (!ft_isalnum(e->line[cur - cpt]))
	{
		cpt = loop_norm_prevw(e, cpt, cur, 0);
		if (cur - cpt > 0 && e->line[cur - cpt])
			cpt = loop_norm_prevw(e, cpt, cur, 1);
	}
	else
		cpt = loop_norm_prevw(e, cpt, cur, 2);
	while (cpt)
	{
		move_left(e);
		cpt--;
	}
}
