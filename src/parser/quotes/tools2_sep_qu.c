/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2_sep_qu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:04:56 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int			chk_xor_bqu(char *tmp, int i, int *flags, t_quote *count)
{
	(void)count;
	if (tmp[i] == '`' && check_back_from(tmp, i - 1) % 2 == 0 &&
		!(*flags & FLAG_QU))
		return (1);
	return (0);
}

int			chk_pr(char *tmp, int i, int *flags, t_quote *count)
{
	if (tmp[i] == '(' && !(*flags & FLAG_DQU) && !(*flags & FLAG_QU) &&
		!count->bq && check_back_from(tmp, i - 1) % 2 == 0)
		return (1);
	return (0);
}

int			chk_less_pr(char *tmp, int i, int *flags, t_quote *count)
{
	if (tmp[i] == ')' && !(*flags & FLAG_DQU) && !(*flags & FLAG_QU) &&
		!count->bq && check_back_from(tmp, i - 1) % 2 == 0)
		return (1);
	return (0);
}
