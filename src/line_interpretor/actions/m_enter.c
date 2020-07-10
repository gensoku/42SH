/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_enter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 09:57:04 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/16 06:36:19 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"
#define EH 		e->heredoc.end_file

static	void	norm_enter_2(t_env *e, char *tmp)
{
	if (e->heredoc.end_file_confirm)
	{
		tmp = ft_strjoin(e->heredoc.end_file_confirm, "\n");
		free(e->heredoc.end_file_confirm);
		e->heredoc.end_file_confirm = ft_strjoin(tmp, e->line);
		ft_memdel((void**)&tmp);
	}
	else
		e->heredoc.end_file_confirm = ft_strdup(e->line);
}

static	void	norm_enter(t_env *e, char *tmp)
{
	(e->heredoc.end_file) ? ft_memdel((void**)&(e->heredoc.end_file)) : 0;
	ft_putchar('\n');
	e->heredoc.end_file_tog = 0;
	if (e->heredoc.end_file_confirm)
	{
		tmp = ft_strjoin(e->heredoc.end_file_confirm, "\n");
		free(e->heredoc.end_file_confirm);
		e->heredoc.end_file_confirm = ft_strdup(tmp);
		ft_memdel((void**)&tmp);
	}
}

static	void	color_clean(t_env *e)
{
	if (e->color_def & COL_EN)
	{
		move_end(e);
		checks_syn_col(e, e->line, *e->cursor, 0);
	}
	else
	{
		ft_del_screen(e->line, 0, e);
		ft_putstr(&e->line[e->cursor->total]);
		tputs(tgetstr("cd", NULL), 1, spec_put);
	}
}

static	void	setup_hist_nl(t_env *e, int on)
{
	if (on)
	{
		write(1, "\n", 1);
		print_curseur(NULL);
		ft_putstr(e->line);
		cursor_set(e, e->cursor, e->line);
	}
	else
		ft_memdel((void **)&e->line);
}

void			move_enter(t_env *e)
{
	int			hist_rep;

	color_clean(e);
	ft_memdel((void **)&e->saved_histo);
	e->saved_histo = ft_strdup(e->line);
	if (e->heredoc.end_file_tog == 1)
	{
		if (e->save_type == 155 || (e->line && ft_strcmp(e->line, EH) == 0))
		{
			norm_enter(e, NULL);
			e->save_type = 0;
			return ;
		}
		norm_enter_2(e, NULL);
	}
	stopped_or_bg(e);
	ft_putstr("");
	hist_rep = check_history_replace(e, 0);
	!hist_rep ? send_instruction(e) : 0;
	ft_memdel((void**)&(e->saved_histo));
	ft_memdel((void **)&e->errno_du_pauvre);
	!hist_rep ? cursor_reset(e) : 0;
	e->tmp_histo = NULL;
	reset_comp(e);
	setup_hist_nl(e, hist_rep);
}
