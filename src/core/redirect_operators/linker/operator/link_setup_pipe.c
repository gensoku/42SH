/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_setup_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 10:58:41 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/19 10:58:43 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	setup_pi(t_token *tmp, t_env *e, int *flag_stop, t_token *node)
{
	(*flag_stop != 1) ? e->last_status = -1 : 0;
	if (tmp->next && tmp->next->tok && check_type_redir(tmp->next) == 1)
	{
		if (*flag_stop == 1)
			run_pipe(tmp, node->first, e);
		else
		{
			reset_fd_(e);
			run_pipe(tmp, NULL, e);
		}
	}
	else
		run_pipe(tmp, node->first, e);
}
