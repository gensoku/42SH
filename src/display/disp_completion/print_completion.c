/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_completion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:59:01 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void			comp_p1(t_env *e, int i)
{
	t_cursor	cur_line;
	char		**tab1;

	ft_del_screen(e->line, 0, e);
	tab1 = ft_strsplit_spec(e->line, 1);
	free(e->line);
	if (tab1)
	{
		while (tab1[i])
			i++;
		if (i > 0)
		{
			ft_memdel((void **)&tab1[i - 1]);
			tab1[i - 1] = ft_strdup(e->comp_exe->name);
		}
	}
	e->line = tab1 ? ft_implode(tab1, ' ') : ft_strdup(e->comp_exe->name);
	cursor_set(e, &cur_line, e->line);
	ft_putstr(e->line);
	cursor_set(e, e->cursor, e->line);
	ft_del_tab(tab1);
	if (cur_line.col == 0 && cur_line.row != 0)
		ft_putchar(' ');
	ft_del_spec_screen(e, 1);
	e->comp_exe = e->comp_exe->next;
}

void					print_comp(t_env *e)
{
	if (e->line && ft_strlen(e->line) != 0)
	{
		if (e->comp_exe)
			comp_p1(e, 0);
		else
			e->comp_exe = NULL;
	}
}
