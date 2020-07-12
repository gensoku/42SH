/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_l_agreg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:05:06 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int		parser_la_gen(char *str, int x, t_parser *tf, int ret)
{
	int			z;

	x++;
	ret++;
	z = 0;
	if (!str[x] || str[x] != '&')
		return (0);
	ret++;
	while (ft_isspace(str[++x]) == 1)
		z++;
	while (str[x] && ft_isdigit(str[x]) == 1)
		tool_incr_(&x, &z, tf, 1);
	(str[x] && str[x] == '-') ? tool_incr_(&x, &z, tf, 1) : (void)x;
	tf->type = L_AGR_REDIR;
	if (str[x] && is_symbol_(str[x]) == 1)
		return (ret + z);
	else if (!str[x])
		return (ret + z);
	else
		return ((str[x - 1] && str[x - 1] == '-') ? (ret + z) : (ret));
	(tf->type == L_AGR_REDIR) ? tf->type = 0 : (void)tf->type;
	tf->agreg_int = 0;
	return (0);
}

static	int		norm_la_pars(char *str, int x, t_parser *tf, int ret)
{
	tool_incr_(&x, &ret, tf, 0);
	while (str[x] && str[x] == ' ')
		tool_incr_(&x, &ret, tf, 0);
	while (ft_isdigit(str[x]) == 1)
		tool_incr_(&x, &ret, tf, 0);
	if (str[x] && str[x] == '<')
		return (parser_la_gen(str, x, tf, ret));
	return (0);
}

int				parser_l_agreg_(char *str, int x, t_parser *tf)
{
	int			ret;

	ret = 0;
	if (str[x] == ' ')
		return (norm_la_pars(str, x, tf, ret));
	else if (x == 0 && str[x] == '<')
		return (parser_la_gen(str, x, tf, ret));
	else if (x == 0 && ft_isdigit(str[x]) == 1)
	{
		tool_incr_(&x, &ret, tf, 0);
		while (ft_isdigit(str[x]) == 1)
			tool_incr_(&x, &ret, tf, 0);
		if (str[x] && str[x] == '<')
			return (parser_la_gen(str, x, tf, ret));
	}
	else if (str[x] == '<')
		return (parser_la_gen(str, x, tf, ret));
	return (0);
}
