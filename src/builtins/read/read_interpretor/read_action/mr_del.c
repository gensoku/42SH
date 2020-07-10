/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_del.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:02:53 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void			cut_norm(void)
{
	tputs(tgetstr("le", NULL), 1, spec_put);
	tputs(tgetstr("dm", NULL), 1, spec_put);
	tputs(tgetstr("dc", NULL), 1, spec_put);
	tputs(tgetstr("ed", NULL), 1, spec_put);
}

static	char			*cut_char(char *line, size_t x, int i, int j)
{
	char	*ret;

	if (!line)
		return (NULL);
	if (x == 0)
		return (line);
	if ((ret = (char *)ft_memalloc(sizeof(char) * ft_strlen(line))) == NULL)
		display_error(-1, "malloc failed char *, exit", get_e(NULL));
	cut_norm();
	while (i < (int)ft_strlen(line))
	{
		if (i == (int)x - 1)
			line[i] = line[i];
		else
		{
			ret[j] = line[i];
			j++;
		}
		i++;
	}
	return (ret);
}

void					r_move_del(t_env *e, int silent)
{
	t_cursor	cur_line;
	char		*tmp;

	if (e->line && e->cursor->total > 0)
	{
		tmp = e->line;
		e->line = cut_char(e->line, e->cursor->total, 0, 0);
		ft_memdel((void**)&tmp);
		ft_del_comp_exe(e);
		cursor_less(e, 1);
		if (!silent)
		{
			tputs(tgetstr("cd", NULL), 1, spec_put);
			ft_putstr(&e->line[e->cursor->total]);
			ft_del_spec_screen(e, 0);
		}
		reset_comp(e);
		if (e->color_def & COL_EN && !silent)
		{
			cursor_set(e, &cur_line, e->line);
			checks_syn_col(e, e->line, *e->cursor, 0);
			(cur_line.col == 0 && cur_line.row != 0) ? ft_putchar(' ') : 0;
			ft_del_spec_screen(e, 1);
		}
	}
}
