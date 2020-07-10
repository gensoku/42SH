/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/16 10:06:32 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		resized_line(t_env *e, int type, int save_total)
{
	type = get_type_prompt(e->flag, e->count_qu);
	tputs(tgetstr("cl", NULL), 1, spec_put);
	if (e->heredoc.end_file_tog)
		heredoc_prompt();
	else if (type)
		print_prompt_quote(type);
	else
		print_curseur(NULL);
	save_total = e->cursor->total;
	cursor_reset(e);
	ft_putstr(e->line);
	cursor_set(e, e->cursor, e->line);
	move_home(e);
	while (save_total)
	{
		move_right(e);
		save_total--;
	}
}

void			resize(int sig)
{
	int				save_total;
	t_env			*e;
	struct winsize	x;
	int				tty;

	e = get_e(NULL);
	tty = ttyslot();
	(!isatty(tty)) ? tty = STDERR_FILENO : 0;
	if (ioctl(tty, TIOCGWINSZ, &x) == -1)
		display_error(-1, ERR_IO, get_e(NULL));
	e->col = x.ws_col;
	e->row = x.ws_row;
	save_total = e->cursor->total;
	(void)sig;
	if (e->line && (int)ft_strlen(e->line) == e->cursor->total)
		cursor_set(e, e->cursor, e->line);
	else if (e->line)
		resized_line(e, 0, save_total);
}
