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

static	void	cut_join(t_env *e)
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
	tputs(tgetstr("cd", NULL), 1, spec_put);
	ft_putstr(&e->line[x]);
	while (e->cursor->total > x + (int)ft_strlen(e->cut))
		move_left(e);
}

void			move_paste(t_env *e)
{
	if (!e->cut)
		return ;
	if (e->line != NULL)
		cut_join(e);
	else
	{
		e->line = ft_strdup(e->cut);
		cursor_set(e, e->cursor, e->line);
		ft_putstr(e->line);
	}
	reset_comp(e);
	if (e->color_def & COL_EN)
	{
		checks_syn_col(e, e->line, *e->cursor, 0);
		ft_del_spec_screen(e, 1);
	}
}
