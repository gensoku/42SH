/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_t_spath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 06:53:18 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			del_t_spath(t_spath *lst)
{
	t_spath	*tmp;
	t_spath	*tmp2;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		del_t_exe(tmp->list);
		tmp->list = NULL;
		free(tmp->name);
		free(tmp);
		tmp = tmp2;
	}
}
