/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_next_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:03:10 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		r_move_next_word(t_env *e, int silent)
{
	int cpt;
	int cur;

	cpt = 0;
	cur = e->cursor->total;
	if (!e->line)
		return ;
	if (!ft_isalnum(e->line[cur]))
	{
		while (e->line[cur + cpt] &&
			!ft_isalnum(e->line[cur + cpt]))
			cpt++;
		if (e->line[cur + cpt])
			while (e->line[cur + cpt] && ft_isalnum(e->line[cur + cpt]))
				cpt++;
	}
	else
	{
		while (e->line[cur + cpt] && ft_isalnum(e->line[cur + cpt]))
			cpt++;
	}
	cpt++;
	while (--cpt)
		r_move_right(e, silent);
}
