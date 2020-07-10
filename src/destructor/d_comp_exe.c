/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_comp_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:12 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void				ft_del_comp_exe(t_env *e)
{
	t_comp			*tmp;
	t_comp			*tmp2;

	if (e->comp_exe)
	{
		tmp = e->comp_exe;
		while (tmp->next)
		{
			tmp2 = tmp;
			tmp = tmp->next;
			if (tmp2->name)
				free(tmp2->name);
			tmp2->name = NULL;
			tmp2 = NULL;
		}
		if (tmp)
		{
			if (tmp->name)
				free(tmp->name);
			tmp->name = NULL;
			tmp = NULL;
		}
		e->comp_exe = NULL;
	}
}
