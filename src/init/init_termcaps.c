/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/22 01:13:06 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	ft_set_caps(t_env *e)
{
	char *term;

	term = NULL;
	if ((term = get_env("TERM", e->env, 1)) == NULL)
	{
		if (e->interactive)
		{
			ft_putstr(MAGENT);
			display_error(0, "term not set, shell probably disfunctional", e);
			ft_putstr(RESET);
		}
		term = ft_strdup("xterm-256color");
	}
	if (tgetent(NULL, term) != 1)
	{
		(term) ? ft_memdel((void**)&term) : (void)term;
		display_error(-1, "Error termcaps setting failed", e);
	}
	(term) ? ft_memdel((void**)&term) : (void)term;
}
