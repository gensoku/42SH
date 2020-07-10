/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_color_act.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:02:45 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		move_color_act(t_env *e)
{
	if (e->heredoc.end_file_tog)
	{
		e->color_def = 0;
		return ;
	}
	e->color_def ^= COL_EN;
	if (e->color_def & COL_EN)
	{
		ft_putstr_fd("\n", 2);
		tputs(tgetstr("cd", NULL), 1, spec_put);
		ft_putstr_fd(MAGENT, 2);
		ft_putstr_fd("Color ENABLED.", 2);
		ft_putstr_fd(RESET, 2);
	}
	else
	{
		ft_putstr_fd("\n", 2);
		tputs(tgetstr("cd", NULL), 1, spec_put);
		ft_putstr_fd("Color DISABLED.", 2);
		ft_putstr_fd(RESET, 2);
	}
	move_ctrl_c(e);
}
