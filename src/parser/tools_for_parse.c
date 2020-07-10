/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:06:02 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

t_pars_cut		*get_helper_cut(void)
{
	t_pars_cut	*node;

	if ((node = (t_pars_cut *)ft_memalloc(sizeof(t_pars_cut))) == NULL)
		display_error(-1, "malloc failed (t_parser), exit", CONTEXT);
	return (node);
}

t_parser		*get_helper_tf(void)
{
	t_parser	*node;

	if (!(node = (t_parser*)ft_memalloc(sizeof(t_parser))))
		display_error(-1, "malloc failed (t_parser), exit", CONTEXT);
	return (node);
}

void			del_t_tools_(t_tools *t)
{
	if (!t)
		return ;
	t->i = 0;
	t->flag_on = 0;
	t->tok = 0;
	t->k = 0;
	t->count_pr = 0;
	t->count_bq = 0;
	t->flag_sp = 0;
	free(t);
}

t_tools			*get_helper_tools_(void)
{
	t_tools		*t;

	if ((t = (t_tools*)ft_memalloc(sizeof(t_tools))) == NULL)
		display_error(-1, "Malloc failed char *, exit", get_e(NULL));
	t->i = 0;
	t->k = 0;
	t->flag_on = 0;
	t->flag_sp = 0;
	t->count_pr = 0;
	t->count_bq = 0;
	t->tok = 0;
	return (t);
}

void			del_t_pars_cut(t_pars_cut *t)
{
	if (!t)
		return ;
	(t->tmp_str) ? ft_memdel((void**)&(t->tmp_str)) : 0;
	t->i = 0;
	t->flag_on = 0;
	t->tok = 0;
	free(t);
}
