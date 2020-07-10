/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_print_current.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 10:36:17 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void				print_current(t_lst_av *tmp)
{
	if (tmp->current == 1)
		tputs(tgetstr("us", NULL), 1, spec_put);
	if (tmp->selected == 1)
		ft_putstr("\033[7m");
	(get_e(NULL)->color_def & COL_EN) ?
		set_color_type(g_sts_f(tmp->name, F_GET_TYPE)) : 0;
	ft_putstr(tmp->name);
	ft_putstr(RESET);
	tputs(tgetstr("ue", NULL), 1, spec_put);
}
