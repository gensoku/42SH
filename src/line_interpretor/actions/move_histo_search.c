/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_histo_search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:03:24 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int	set_histo_search(t_env *e, t_histo *list)
{
	t_histo	*tmp;

	if (!list)
		return (0);
	tmp = list;
	while (tmp)
	{
		if (ft_strstr(tmp->name, e->line) != NULL)
		{
			e->tmp_histo = tmp;
			set_current_histo(e);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void		move_ctrl_r(t_env *e)
{
	if (!e->line)
		return ;
	else
	{
		if (e->tmp_histo)
		{
			if (!set_histo_search(e, e->tmp_histo))
				set_histo_search(e, e->histo);
		}
		else if (e->histo)
			set_histo_search(e, e->histo);
	}
}
