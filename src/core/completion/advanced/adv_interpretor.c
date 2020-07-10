/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_interpretor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 10:51:40 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:48:54 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			interpretor(int x, t_env *e, t_cursor *all)
{
	if (x == 0x1b)
		code_exit(e);
	if (x == 4283163)
		arrow_up_(e, all);
	if (x == 4348699)
		arrow_down_(e, all);
	if (x == 4479771)
		arrow_left_(e, all);
	if (x == 4414235)
		arrow_right_(e, all);
	if (x == 32)
		select_cur(e, all);
	if (x == 10)
		enter(e);
	if (x == 21)
		code_exit(e);
}
