/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:05:11 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		parser_red_gen_(char *str, int x, t_parser *tf, int ret)
{
	x++;
	ret++;
	if (str[x] && str[x] == '>')
	{
		tf->type = R_D_REDIR;
		return (ret + 1);
	}
	else if (str[x] && str[x] == '|')
	{
		tf->type = R_REDIR;
		return (ret + 1);
	}
	else if (str[x] && str[x] == '&')
		return (0);
	tf->type = R_REDIR;
	return (ret);
}

static	int		norm_une_ligne(char *str, int x, t_parser *tf, int ret)
{
	tool_incr_(&x, &ret, tf, 0);
	while (str[x] && str[x] == ' ')
		tool_incr_(&x, &ret, tf, 0);
	while (ft_isdigit(str[x]) == 1)
		tool_incr_(&x, &ret, tf, 0);
	if (str[x] && str[x] == '>')
		return (parser_red_gen_(str, x, tf, ret));
	return (0);
}

int				parser_right_(char *str, int x, t_parser *tf)
{
	int ret;

	ret = 0;
	if (str[x] == ' ')
		return (norm_une_ligne(str, x, tf, ret));
	else if (x == 0 && str[x] == '>')
		return (parser_red_gen_(str, x, tf, ret));
	else if (x == 0 && ft_isdigit(str[x]) == 1)
	{
		tool_incr_(&x, &ret, tf, 0);
		while (ft_isdigit(str[x]) == 1)
			tool_incr_(&x, &ret, tf, 0);
		if (str[x] && str[x] == '>')
			return (parser_red_gen_(str, x, tf, ret));
	}
	else if (str[x] == '>')
		return (parser_red_gen_(str, x, tf, ret));
	return (0);
}
