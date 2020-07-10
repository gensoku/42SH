/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_pars_agr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:05:25 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			tool_incr_(int *x, int *z, t_parser *tf, int opt)
{
	++*x;
	++*z;
	(opt) ? tf->agreg_int = 1 : 0;
}

int				is_symbol_(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	if (c == '&')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}
