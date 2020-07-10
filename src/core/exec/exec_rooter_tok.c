/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_rooter_tok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 09:35:51 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 09:45:18 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int		rooteur_(t_token *tmp, t_env *e, int flag_stop,
	int (*func)(t_token *, t_env *e))
{
	if (!func)
		return (flag_stop);
	(flag_stop != 1) ? e->last_status = -1 : 0;
	if (tmp->errno_node || func(tmp, e) == -1)
	{
		(tmp->errno_node) ? ft_putendl_fd(tmp->errno_node, 2) : 0;
		e->last_status = 1;
		return (0);
	}
	else
		e->last_status = 0;
	return (flag_stop);
}

static	int		(*get_nb_red(int type))(t_token *, t_env *)
{
	static t_red_func	all_redir[] = {
		{R_A_RED, link_right_agreg},
		{L_AGR_REDIR, link_left_agreg},
		{R_REDIR, link_tok_right},
		{R_D_REDIR, link_tok_right2},
		{L_REDIR, link_tok_left},
		{0, NULL}};
	t_red_func			*f;

	f = all_redir;
	while (f->f)
		if (f->code == type)
			return (f->f);
		else
			f++;
	return (NULL);
}

static void		(*get_setup(int type))(void *, void *, void *, void *)
{
	static t_set_funcs	setups[] = {
		{P_REDIR, (t_set_func)setup_pi},
		{BACK_PROCESS_REDIR, (t_set_func)setup_background},
		{SUB_RED, (t_set_func)sub_setup},
		{0, 0}
	};
	t_set_funcs			*f;

	f = setups;
	while (f->f)
		if (f->code == type)
			return (f->f);
		else
			f++;
	return (NULL);
}

static	void	root_tk_n(t_token *node, t_env *e, t_token *tmp, int flag_stop)
{
	void	(*f)(void *, void *, void *, void *);

	tmp = node;
	while (tmp)
	{
		e->foreground = tmp->foreground;
		flag_stop = rooteur_(tmp, e, flag_stop, get_nb_red(tmp->type));
		(flag_stop != 1) ? e->last_status = -1 : 0;
		if ((f = get_setup(tmp->type)))
			f(tmp, e, &flag_stop, node);
		else if (tmp->type == AND_RE)
			setup_and_or(tmp, e, &run_and, node);
		else if (tmp->type == OR_RE)
			setup_and_or(tmp, e, run_or, node);
		if (tmp->type == P_REDIR || tmp->type == AND_RE || tmp->type ==
			OR_RE || tmp->type == BACK_PROCESS_REDIR || tmp->type == SUB_RED)
			return ;
		tmp = tmp->previous;
	}
	(!check_type_redir(node) || flag_stop == 1) ?
		exec_tok(node->first, e, 1) : 0;
}

void			root_tok(t_token *node, t_env *e)
{
	reset_fd_(e);
	root_tk_n(node, e, NULL, 1);
}
