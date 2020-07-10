/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_launcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:04:41 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		append_load_ins(t_env *e, int type)
{
	char	*tmp;

	tmp = NULL;
	if (type < 0)
		display_qu_error(type);
	else if (e->save_quote)
	{
		tmp = ft_strjoin(e->save_quote, e->line);
		save_histo_(e, tmp);
		instruction(tmp, SUB_FALSE, e);
		ft_memdel((void**)&(e->save_quote));
	}
	else
	{
		(e->line && ft_strlen(e->line) > 0) ? save_histo_(e, e->line) : 0;
		instruction(e->line, SUB_FALSE, e);
	}
	ft_memdel((void **)&e->save_quote);
	ft_bzero((void *)e->count_qu, 12);
	e->flag = 0;
	ft_memdel((void**)&tmp);
	print_curseur(NULL);
}
