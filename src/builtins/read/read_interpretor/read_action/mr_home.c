/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_home.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:03:01 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			r_move_home(t_env *e, int silent)
{
	if (!e->line)
		return ;
	while (e->cursor->total != 0)
		r_move_left(e, silent);
}
