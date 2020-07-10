/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_r_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 09:41:53 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/24 09:41:54 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		check_delim(int x, unsigned long opts, char opt_arg)
{
	if (is_opt_set(opts, 'd') && x == opt_arg)
		return (1);
	else if (!is_opt_set(opts, 'd') && (x == '\n' || x == EOF))
		return (1);
	return (0);
}

int				move_treatment(t_read *r)
{
	char		*set_reply;
	char		*reply;

	(is_opt_set(r->opts, 'r') && CTX(line)) ?
		read_add_bkslsh(&CTX(line), "\\") : 0;
	if (((r->args && !(*r->args)) || !r->args) && !is_opt_set(r->opts, 'a'))
	{
		if (!(update_var("REPLY", CTX(line), CONTEXT)))
		{
			set_reply = ft_strjoin("REPLY", "=");
			reply = ft_strjoin(set_reply, CTX(line));
			set_var_(reply, LOC_VAR, VAR_NEUTRAL);
			ft_memdel((void **)&reply);
			ft_memdel((void **)&set_reply);
		}
	}
	else if (is_opt_set(r->opts, 'a'))
		read_into_array(r);
	else if (r->args)
		read_into_args(r);
	return (1);
}

static int		mo_r_display_2(long x, t_env *e, int trigger)
{
	if (x == 25)
		r_move_paste(e, trigger);
	else if (x == 0x485b1b || x == 1)
		r_move_home(e, trigger);
	else if (x == 0x465b1b || x == 5)
		r_move_end(e, trigger);
	else if (x == 2117425947)
		r_move_mult_up(e, trigger);
	else if (x == 2117491483)
		r_move_mult_do(e, trigger);
	else if (x == 14)
		r_move_next_word(e, trigger);
	else if (x == 2)
		r_move_previous_word(e, trigger);
	else if (x == 0x5a5b1b && e->heredoc.end_file_tog == 0 && !trigger)
		move_tab_spec(e);
	else if (x == 18 && !trigger)
		move_ctrl_r(e);
	else if (x == 4 && (!e->line || !ft_strlen(e->line)))
		return (1);
	return (0);
}

static int		mo_r_display_3(long x, t_env *e, int trigger)
{
	if (x == 0x7f)
		r_move_del(e, trigger);
	else if (x == 9 && !trigger)
		move_tab(e);
	else if (x == 3 && e->heredoc.end_file_tog == 0 && !trigger)
		return (r_move_ctrl_c(e));
	else if (x == 4479771)
		r_move_left(e, trigger);
	else if (x == 4414235)
		r_move_right(e, trigger);
	else if (x == 4348699 && !trigger)
		move_down(e);
	else if (x == 4283163 && !trigger)
		move_up(e);
	else if (ft_isprint(x))
		r_move_add_(x, e, trigger);
	else if (x == 12 && e->heredoc.end_file_tog == 0)
		r_move_ctrl_l(e, trigger);
	else if (x == 11)
		r_move_cut(e, trigger);
	else
		return (mo_r_display_2(x, CONTEXT, trigger));
	return (0);
}

int				mo_r_display(int x, t_read *r)
{
	t_env		*e;
	int			trigger;

	e = get_e(NULL);
	trigger = (is_opt_set(r->opts, 's')) ? 1 : 0;
	if (check_delim(x, r->opts, r->delim))
		return (move_treatment(r));
	if (!is_opt_set(r->opts, 'e'))
	{
		if (ft_isprint(x))
			r_move_add_(x, CONTEXT, trigger);
		else if (x == 3)
			return (r_move_ctrl_c(e));
		else if (x == 0x7f)
			r_move_del(e, trigger);
		return (0);
	}
	else
		return (mo_r_display_3(x, CONTEXT, trigger));
	return (0);
}
