/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_loop_interpretor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:48:57 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			get_inter(t_env *e, t_cursor *all)
{
	char		buf[4];
	int			x;

	tputs(tgetstr("vi", NULL), 1, spec_put);
	reset_print(e, all);
	buf[0] = 0;
	while (buf[0] != 4)
	{
		buf[0] = 0;
		buf[1] = 0;
		buf[2] = 0;
		buf[3] = 0;
		read(0, buf, 4);
		x = (buf[3] << 24) + (buf[2] << 16) + (buf[1] << 8) + buf[0];
		interpretor(x, e, all);
		if (e->stop_comp == 1)
			break ;
	}
	reset_print(e, all);
	tputs(tgetstr("ve", NULL), 1, spec_put);
}
