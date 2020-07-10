/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_t_lst_av.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:33 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			del_t_lst_av(t_lst_av *lst)
{
	t_lst_av *tmp;
	t_lst_av *tmp2;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_memdel((void*)tmp->name);
		ft_memdel((void*)tmp);
		tmp = tmp2;
	}
}
