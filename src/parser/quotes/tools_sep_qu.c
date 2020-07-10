/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_sep_qu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:04:58 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int			chk_less_dqu(char *tmp, int i, int *flags, t_quote *count)
{
	int				len;

	len = ft_strlen(tmp);
	if ((tmp[i] == '"' && (*flags & FLAG_DQU)) &&
			(len == 1 || check_back_from(tmp, i - 1) % 2 == 0) && !count->bq)
		return (1);
	return (0);
}

int			chk_dqu(char *tmp, int i, int *flags, t_quote *count)
{
	int				len;

	len = ft_strlen(tmp);
	if (tmp[i] == '"' && (len == 1 || check_back_from(tmp, i - 1) % 2 == 0) &&
		!(*flags & FLAG_QU) && !count->bq)
		return (1);
	return (0);
}

int			chk_less_qu(char *tmp, int i, int *flags, t_quote *count)
{
	int				len;

	len = ft_strlen(tmp);
	if (tmp[i] == '\'' && (*flags & FLAG_QU) && !count->bq && (len == 1
		|| check_back_from(tmp, i - 1) % 2 == 0))
		return (1);
	return (0);
}

int			chk_qu(char *tmp, int i, int *flags, t_quote *count)
{
	int				len;

	len = ft_strlen(tmp);
	if (tmp[i] == '\'' && (len == 1 || check_back_from(tmp, i - 1) % 2 == 0) &&
		!(*flags & FLAG_DQU) && !count->bq)
		return (1);
	return (0);
}
