/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_full_completion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:59:03 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		disp_1(t_env *e, int x_max)
{
	t_cursor cur_line;

	cursor_set(e, e->cursor, e->line);
	x_max = e->cursor->row;
	while (x_max)
	{
		tputs(tgetstr("up", NULL), 1, spec_put);
		x_max--;
	}
	tputs(tgetstr("cr", NULL), 1, spec_put);
	tputs(tgetstr("cd", NULL), 1, spec_put);
	print_curseur(NULL);
	e->comp_screen = 1;
	cursor_set(e, &cur_line, e->line);
	ft_putstr(e->line);
	if (cur_line.col == 0 && cur_line.row != 0)
		ft_putchar(' ');
	ft_del_spec_screen(e, 1);
}

static void		disp_2(t_env *e, int x_max)
{
	t_cursor cur_line;

	x_max++;
	x_max += e->cursor->row;
	while (x_max)
	{
		tputs(tgetstr("up", NULL), 1, spec_put);
		x_max--;
	}
	tputs(tgetstr("cr", NULL), 1, spec_put);
	x_max = 0;
	while (x_max < get_size_prompt(NULL))
	{
		tputs(tgetstr("nd", NULL), 1, spec_put);
		x_max++;
	}
	cursor_set(e, &cur_line, e->line);
	ft_putstr(e->line);
	if (cur_line.col == 0 && cur_line.row != 0)
		ft_putchar(' ');
	ft_del_spec_screen(e, 1);
}

static void		disp_3(char **tab1, int max, int x_max, int col)
{
	ft_putchar('\n');
	print_tab1_col(tab1, max, x_max, col);
}

void			display_all(char **tab1, t_env *e, int size, int i)
{
	int	max;
	int	col;
	int	x_max;

	x_max = 0;
	(void)i;
	max = get_size_len(tab1);
	col = (e->col / max);
	x_max = (size / col) + 1;
	if (x_max >= e->row)
	{
		if (e->comp_screen != 1)
		{
			disp_3(tab1, max, x_max, col);
			print_curseur(NULL);
		}
		disp_1(e, x_max);
	}
	else
	{
		disp_3(tab1, max, x_max, col);
		disp_2(e, x_max);
	}
}
