/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_clear_display.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:55 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int					adv_aa_1(t_cursor *all, int i, t_lst_av *tmp)
{
	if (i < all->total)
	{
		print_current(tmp);
		ft_putspace(ft_strlen(tmp->name), all->col);
		i++;
	}
	else
	{
		ft_putchar('\n');
		print_current(tmp);
		ft_putspace(ft_strlen(tmp->name), all->col);
		i = 1;
	}
	return (i);
}

static	void				print_tab1_col2(t_env *e, t_cursor *all)
{
	t_lst_av		*tmp;
	t_lst_av		*head;
	int				i;
	int				flag;

	tmp = e->auto_c;
	head = e->auto_c;
	i = 0;
	flag = 0;
	while (tmp && head && (tmp != head || flag == 0))
	{
		i = adv_aa_1(all, i, tmp);
		tmp = tmp->next;
		flag++;
	}
}

static	void				help_m_up(int cp)
{
	while (cp > 0)
	{
		tputs(tgetstr("up", NULL), 1, spec_put);
		cp--;
	}
}

static	void				help_m_prompt(int cp)
{
	while (cp < get_size_prompt(NULL))
	{
		tputs(tgetstr("nd", NULL), 1, spec_put);
		cp++;
	}
}

void						reset_print(t_env *e, t_cursor *all)
{
	int				cp;
	t_cursor		cur_line;

	cp = all->row;
	ft_putchar('\n');
	tputs(tgetstr("cd", NULL), 1, spec_put);
	print_tab1_col2(e, all);
	cp += e->cursor->row;
	help_m_up(cp);
	tputs(tgetstr("cr", NULL), 1, spec_put);
	cp = 0;
	help_m_prompt(0);
	cursor_set(e, &cur_line, e->line);
	ft_putstr(e->line);
	(cur_line.col == 0 && cur_line.row != 0) ? ft_putchar(' ') : 0;
	ft_del_spec_screen(e, 1);
}
