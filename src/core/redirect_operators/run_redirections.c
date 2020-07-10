/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 09:45:12 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int				check_valid_tok(t_token *node, t_env *e)
{
	if (!node || !node->tok)
		return (-1);
	if (node->tok)
	{
		if (node->type == R_REDIR && e->last_status == 0)
			return (run_tok_right(node));
		else if (node->type == R_D_REDIR && e->last_status == 0)
			return (run_tok_right2(node));
		else if (node->type == L_REDIR && e->last_status == 0)
			return (run_tok_left(node));
		else if (node->type == R_A_RED && e->last_status == 0)
			return (run_right_agreg(node, e));
		else if (node->type == L_AGR_REDIR && e->last_status == 0)
			return (run_left_agreg(node, e));
		else
			e->last_status = 0;
	}
	return (e->last_status);
}
