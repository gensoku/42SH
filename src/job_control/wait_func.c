/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/19 09:45:18 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		still_running(pid_t pgid, t_env *e)
{
	t_childs	*tmp;

	tmp = e->childs;
	while (tmp)
	{
		if (tmp->grpid == pgid)
		{
			if (tmp->stopped != 1 && tmp->foreground)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void			wait_pgid(pid_t pgid, t_env *e, int opt)
{
	while (still_running(pgid, e))
		wait_process(e, opt);
}

void			add_background_to_process(t_token *list)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == BACK_PROCESS_REDIR)
		{
			tmp2 = tmp->next;
			tmp->foreground = 0;
			while (tmp2)
			{
				if (tmp2->type != BACK_PROCESS_REDIR && tmp2->type !=
					OR_RE && tmp2->type != AND_RE)
				{
					tmp2->foreground = 0;
					tmp2 = tmp2->next;
				}
				else
					break ;
			}
		}
		tmp = tmp->previous;
	}
}
