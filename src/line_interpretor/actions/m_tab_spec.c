/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_tab_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:03:20 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		norm_join(t_env *e, char *join, int i)
{
	t_cursor	cur_line;
	char		**tab1;

	ft_del_screen(e->line, 0, e);
	tab1 = ft_strsplit(e->line, ' ');
	free(e->line);
	if (tab1)
	{
		while (tab1[i])
			i++;
		if (tab1[i - 1])
			free(tab1[i - 1]);
		tab1[i - 1] = ft_strdup(join);
	}
	e->line = ft_implode(tab1, ' ');
	cursor_set(e, &cur_line, e->line);
	ft_putstr(e->line);
	cursor_set(e, e->cursor, e->line);
	ft_del_tab(tab1);
	if (cur_line.col == 0 && cur_line.row != 0)
		ft_putchar(' ');
	ft_del_spec_screen(e, 1);
}

void			print_comp2(t_env *e, char *join)
{
	if (e->line && ft_strlen(e->line) != 0)
	{
		if (join)
			norm_join(e, join, 0);
	}
}

static void		split_tab_spec(t_env *e)
{
	char *save;

	save = ft_strdup(e->line);
	if (auto_comp(e) != 0)
		aac_p1(e, save);
	else if (e->ret_comp)
		aac_p2(e);
	else
		tputs(tgetstr("cd", NULL), 1, spec_put);
	e->stop_comp = 0;
	free(save);
	save = NULL;
	reset_comp(e);
}

void			move_tab_spec(t_env *e)
{
	char *save;

	if (!e->comp_path)
	{
		save = (e->line) ? ft_strdup(e->line) : NULL;
		searcher(e, 1);
		if (!e->comp_path)
		{
			(save) ? ft_memdel((void**)&save) : (void)save;
			return ;
		}
		if (auto_comp(e) != 0)
			aac_p1(e, save);
		else if (e->ret_comp)
			aac_p2(e);
		else
			aac_p3(e, save);
		ft_memdel((void **)&save);
		e->stop_comp = 0;
	}
	else
		split_tab_spec(e);
	reset_comp(e);
}
