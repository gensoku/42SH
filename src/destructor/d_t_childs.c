/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_t_childs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:21 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			del_t_childs(t_childs *lst)
{
	t_childs *tmp;
	t_childs *tmp2;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		kill(tmp->child, 9);
		(tmp->name) ? ft_memdel((void**)&(tmp->name)) : (void)tmp->name;
		ft_memdel((void**)&tmp);
		tmp = tmp2;
	}
}
