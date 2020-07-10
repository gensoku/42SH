/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_paste.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:03:12 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	char	*set_new_line(t_env *e, char c, int size)
{
	char		*new_line;

	new_line = ft_strnew(size);
	c = 0;
	if (e->line[e->cursor->total])
	{
		c = e->line[e->cursor->total];
		e->line[e->cursor->total] = 0;
	}
	ft_bzero(new_line, size);
	ft_strcat(new_line, e->line);
	ft_strcat(new_line, e->cut);
	if (c != 0)
	{
		e->line[e->cursor->total] = c;
		ft_strcat(new_line, &(e->line[e->cursor->total]));
	}
	return (new_line);
}

static	void	cut_join(t_env *e, int silent)
{
	int		size;
	char	*new_line;
	int		x;

	size = ft_strlen(e->line) + ft_strlen(e->cut) + 1;
	new_line = set_new_line(e, 0, size);
	x = e->cursor->total;
	ft_memdel((void **)&e->line);
	e->line = new_line;
	cursor_set(e, e->cursor, e->line);
	if (!silent)
	{
		tputs(tgetstr("cd", NULL), 1, spec_put);
		ft_putstr(&e->line[x]);
	}
	while (e->cursor->total > x + (int)ft_strlen(e->cut))
		r_move_left(e, silent);
}

void			r_move_paste(t_env *e, int silent)
{
	if (!e->cut)
		return ;
	if (e->line != NULL)
		cut_join(e, silent);
	else
	{
		e->line = ft_strdup(e->cut);
		cursor_set(e, e->cursor, e->line);
		(!silent) ? ft_putstr(e->line) : 0;
	}
	reset_comp(e);
	if (e->color_def & COL_EN && !silent)
	{
		checks_syn_col(e, e->line, *e->cursor, 0);
		ft_del_spec_screen(e, 1);
	}
}
