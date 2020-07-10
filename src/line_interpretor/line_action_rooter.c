/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_action_rooter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 07:25:22 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:04:39 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		moves_display_2(long x, t_env *e)
{
	if (x == 25)
		move_paste(e);
	else if (x == 0x485b1b || x == 1)
		move_home(e);
	else if (x == 0x465b1b || x == 5)
		move_end(e);
	else if (x == 2117425947)
		move_mult_up(e);
	else if (x == 2117491483)
		move_mult_do(e);
	else if (x == 14)
		move_next_word(e);
	else if (x == 2)
		move_previous_word(e);
	else if (x == 0x5a5b1b && e->heredoc.end_file_tog == 0)
		move_tab_spec(e);
	else if (x == 16)
		move_reset_hash(e);
	else if (x == 18)
		move_ctrl_r(e);
	else if (x == 21)
		move_color_act(e);
}

void			moves_display(long x, t_env *e)
{
	(e->heredoc.end_file_tog) ? e->color_def = 0 : 0;
	if (x == 0x7f)
		move_del(e);
	else if (x == 9)
		move_tab(e);
	else if (x == 3 && e->heredoc.end_file_tog == 0)
		move_ctrl_c(e);
	else if (x == 4479771)
		move_left(e);
	else if (x == 4414235)
		move_right(e);
	else if (x == 4348699)
		move_down(e);
	else if (x == 4283163)
		move_up(e);
	else if (ft_isprint(x) == 1)
		move_add_(x, e);
	else if (x == 0xa)
		move_enter(e);
	else if (x == 12 && e->heredoc.end_file_tog == 0)
		move_ctrl_l(e);
	else if (x == 11)
		move_cut(e);
	else
		moves_display_2(x, e);
}
