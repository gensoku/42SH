/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_t_comp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:23 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			del_t_comp(t_comp *lst)
{
	t_comp *tmp;
	t_comp *tmp2;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		(tmp->name) ? free(tmp->name) : (void)tmp->name;
		tmp->name = NULL;
		free(tmp);
		tmp = tmp2;
	}
}
