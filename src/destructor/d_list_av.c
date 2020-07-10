/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_list_av.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:15 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	del_list_av(t_env *e)
{
	t_lst_av *tmp;
	t_lst_av *tmp2;

	tmp = e->auto_c;
	e->cur_node = NULL;
	tmp2 = NULL;
	while (tmp)
	{
		tmp2 = NULL;
		if (tmp->name)
		{
			free(tmp->name);
			tmp->name = NULL;
			tmp->next = NULL;
			tmp->previous = NULL;
			tmp2 = tmp->next;
			free(tmp);
		}
		tmp = tmp2;
	}
	e->auto_c = NULL;
}
