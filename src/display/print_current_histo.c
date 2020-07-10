/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_current_histo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:59:13 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	set_current_histo(t_env *e)
{
	t_cursor cur_line;

	cursor_set(e, &cur_line, e->line);
	ft_del_screen(e->line, e->cursor->total, e);
	if (e->line)
		free(e->line);
	e->line = ft_strdup(e->tmp_histo->name);
	cursor_set(e, &cur_line, e->line);
	ft_putstr(e->line);
	if (cur_line.col == 0 && cur_line.row != 0)
	{
		ft_putchar(' ');
		tputs(tgetstr("le", NULL), 1, spec_put);
	}
	cursor_set(e, e->cursor, e->line);
	reset_comp(e);
}
