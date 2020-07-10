/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_add.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 08:53:57 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void			norme_add_char(t_env *e, char c, size_t x, size_t i)
{
	char *ret;

	if ((ret = (char *)malloc(sizeof(char)
	* ft_strlen(e->line) + 2)) == NULL)
		display_error(-1, "malloc failed char *, exit", e);
	while (e->line && e->line[i] && i < x)
	{
		ret[i] = e->line[i];
		i++;
	}
	ret[i] = c;
	while (e->line[i])
	{
		ret[i + 1] = e->line[i];
		i++;
	}
	ret[i + 1] = 0;
	free(e->line);
	e->line = ret;
}

static	void		add_char(t_env *e, int c, size_t x)
{
	char		*ret;

	ret = NULL;
	if (!e->line)
	{
		if ((ret = (char *)malloc(sizeof(char) * 2)) == NULL)
			display_error(-1, "malloc failed char *, exit", e);
		ret[0] = c;
		ret[1] = 0;
		e->line = ret;
	}
	else
		norme_add_char(e, c, x, 0);
}

void				move_add_(int x, t_env *e)
{
	t_cursor		cur_line;

	add_char(e, x, e->cursor->total);
	ft_putstr(&e->line[e->cursor->total]);
	cursor_add(e, 1);
	cursor_set(e, &cur_line, e->line);
	(cur_line.col == 0 && cur_line.row != 0) ? ft_putchar(' ') : 0;
	ft_del_spec_screen(e, 1);
	reset_comp(e);
	if (e->color_def & COL_EN)
	{
		checks_syn_col(e, e->line, *e->cursor, 0);
		(cur_line.col == 0 && cur_line.row != 0) ? ft_putchar(' ') : 0;
		ft_del_spec_screen(e, 1);
	}
}
