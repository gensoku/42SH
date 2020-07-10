/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_exe_background.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 08:27:47 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/19 08:27:48 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	setup_background(t_token *tmp, t_env *e, int *flag_stop, t_token *node)
{
	(*flag_stop != 1) ? e->last_status = -1 : 0;
	e->display_bg = 1;
	exec_tok(node->first, e, 1);
	e->display_bg = 0;
	wait_pgid(e->tmp_pgid, e, 0);
	resume_state(e, 2, NULL);
	if (tmp->previous)
		root_tok(tmp->previous, e);
	else if (tmp->second)
		exec_tok(node->second, e, 1);
}
