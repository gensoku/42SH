/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:04:54 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int			get_type_prompt(int flag, t_quote *count)
{
	if (count->pr < 0)
		return (-1);
	if (count->bq < 0)
		return (-2);
	if (count->ac < 0)
		return (-3);
	if (count->bq > 0)
		return (2);
	if (flag == 0)
	{
		if (count->pr > 0)
			return (1);
		if (count->ac > 0)
			return (3);
	}
	else
	{
		if (flag & FLAG_QU)
			return (4);
		if (flag & FLAG_DQU)
			return (5);
		if (flag & FLAG_BACK)
			return (6);
	}
	return (0);
}
