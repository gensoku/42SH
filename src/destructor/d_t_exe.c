/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_t_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:26 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			del_t_exe(t_exe *lst)
{
	if (lst->next)
		del_t_exe(lst->next);
	if (lst)
	{
		ft_memdel((void**)&lst->name);
		ft_memdel((void**)&lst->path);
		ft_memdel((void**)&lst->full_name);
		ft_memdel((void**)&lst);
	}
}
