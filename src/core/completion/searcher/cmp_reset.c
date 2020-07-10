/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_reset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:49:18 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		reset_comp(t_env *e)
{
	del_t_comp(e->comp_path);
	(e->auto_c) ? del_t_lst_av(e->auto_c) : (void)e;
	e->auto_c = NULL;
	e->cur_node = NULL;
	e->comp_screen = 0;
	e->comp_exe = NULL;
	e->comp_path = NULL;
}
