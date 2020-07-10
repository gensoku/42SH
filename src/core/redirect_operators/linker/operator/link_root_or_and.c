/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_root_or_and.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 11:00:52 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/19 11:00:53 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	setup_and_or(t_token *tmp, t_env *e,
	void (*func)(t_token *t, char *s, t_env *e), t_token *node)
{
	if (tmp->next && tmp->next->tok && check_type_redir(tmp->next) == 0)
		func(tmp, NULL, e);
	else
		func(tmp, node->first, e);
}
