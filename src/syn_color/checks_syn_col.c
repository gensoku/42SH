/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_syn_col.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 05:12:03 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/28 05:12:05 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void		setup_loc_col(char *file, char c, char *col)
{
	col ? ft_putstr_fd(col, 2) : 0;
	file ? ft_putstr_fd(file, 2) : ft_putchar_fd(c, 2);
	ft_putstr_fd(RESET, 2);
}

static	void		syn_print_with_type(char *file, int type)
{
	t_exe			*tmp;

	if ((type >= 1 && type <= 5) || type == 7)
	{
		set_color_type(type);
		setup_loc_col(file, 0, NULL);
	}
	else
	{
		if (get_builtin(&file, CONTEXT, NO_EXEC) == 1)
			setup_loc_col(file, 0, MAGENT_H);
		else if ((tmp = get_exe_hash(file, CONTEXT)))
			setup_loc_col(file, 0, CYAN_H);
		else if (type == 6)
			setup_loc_col(file, 0, WHITE);
		else
			setup_loc_col(file, 0, WHITE_H);
	}
}

void				tool_norm_syn_col(int i, int k, char *line, int opt)
{
	char		*arg;

	arg = NULL;
	if (k && (arg = ft_strsub(line, i - k, k)))
	{
		syn_print_with_type(arg, g_sts_f(arg, F_GET_TYPE));
		ft_memdel((void **)&arg);
	}
	if (opt && opt != -1)
		setup_loc_col(NULL, line[i], opt == 1 ? BLUE : YELLOW);
	else if (!opt)
		ft_putchar_fd(' ', 2);
}

static	void		syn_print_tok(char *line, int i, int k, int flags)
{
	t_quote			qu;

	ft_bzero(&qu, sizeof(t_quote));
	while (line[++i])
	{
		if (set_sep_flags(line, i, &flags, &qu))
		{
			tool_norm_syn_col(i, k, line, 1);
			k = 0;
		}
		else if (is_a_tok(line[i]) && flags == 0)
		{
			tool_norm_syn_col(i, k, line, 2);
			k = 0;
		}
		else if (ft_isspace(line[i]) && !flags)
		{
			tool_norm_syn_col(i, k, line, 0);
			k = 0;
		}
		else
			k++;
	}
	tool_norm_syn_col(i, k, line, -1);
}

void				checks_syn_col(t_env *e, char *arg, t_cursor save, int opts)
{
	char			*line;
	t_cursor		real_save;

	real_save = save;
	if (!arg || !ft_strlen(arg) || !(e->color_def & COL_EN))
		return ;
	if (!(line = ft_strdup(arg)))
		return ;
	move_home(e);
	tputs(tgetstr("cd", NULL), 1, spec_put);
	syn_print_tok(line, -1, 0, 0);
	e->cursor->col = real_save.col;
	e->cursor->row = real_save.row;
	e->cursor->total = real_save.total;
	ft_memdel((void **)&line);
	(void)opts;
}
