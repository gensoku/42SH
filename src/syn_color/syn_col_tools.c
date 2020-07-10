/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syn_col_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 06:28:06 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/01 06:28:07 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			check_bord_term(t_env *e)
{
	t_cursor	cur;

	if (!e->line)
		return ;
	cursor_set(e, &cur, e->line);
	if (cur.col == 0 && cur.row != 0)
		ft_putstr("\n");
}

int				is_a_tok(char c)
{
	if (c == '|' || c == '&' || c == '>' || c == '<' || c == ';')
		return (1);
	return (0);
}
