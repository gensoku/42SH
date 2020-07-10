/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_exe_and.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:56:01 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			run_and(t_token *node, char *save, t_env *e)
{
	t_token *tmp;

	tmp = node->next;
	if (node->next && check_type_redir(node) && e->last_status != 0)
		;
	else
		exec_tok(save ? save : node->first, e, 1);
	wait_pgid(e->tmp_pgid, e, 0);
	resume_state(e, 2, NULL);
	if (e->last_status != 0)
		return ;
	else if (node->previous)
		root_tok(node->previous, e);
	else
		exec_tok(node->second, e, 1);
}
