/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 09:19:04 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/22 02:20:21 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int				check_redirect_2(t_token *lst, t_env *e)
{
	t_token *tmp;

	tmp = lst;
	e->last_status = 0;
	while (tmp)
	{
		e->last_status = check_valid_tok(tmp, e);
		tmp = tmp->previous;
	}
	return (0);
}

void					update_ret_value(t_env *e)
{
	char				*val;
	char				*set_var;

	val = ft_itoa(e->last_status);
	if (!update_var("?", val, e))
	{
		set_var = ft_strjoin("?=", val);
		set_var_(set_var, LOC_VAR, VAR_X);
		ft_memdel((void **)&set_var);
	}
	(val) ? ft_memdel((void **)&val) : 0;
}

static	void			loop_call_setup(t_token *tmp, t_env *e)
{
	if (e->heredoc_null)
	{
		add_background_to_process(tmp);
		root_tok(tmp, e);
		wait_pgid(e->tmp_pgid, e, 0);
		resume_state(e, 1, tmp);
	}
	else if (!heredoc_launcher(tmp, e, 0))
	{
		add_background_to_process(tmp);
		root_tok(tmp, e);
		wait_pgid(e->tmp_pgid, e, 0);
		resume_state(e, 1, tmp);
	}
}

void					check_redir_exec(t_env *e, t_token *tmp)
{
	if (!tmp->tok)
	{
		if (!exec_tok(tmp->first, e, 1))
		{
			if (e->childs)
			{
				wait_pgid(e->childs->child, e, 0);
				resume_state(e, 0, NULL);
			}
		}
	}
	else if (check_redirect_2(tmp, e) == 0)
		loop_call_setup(tmp, e);
	e->save_type = 0;
	update_ret_value(e);
}
