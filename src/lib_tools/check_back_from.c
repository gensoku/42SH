/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_back_from.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:01:29 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int			check_back_from(char *str, int i)
{
	int ret;

	ret = 0;
	if (!str)
		return (-1);
	while (i >= 0 && str[i] && str[i] == '\\')
	{
		ret++;
		i--;
	}
	return (ret);
}
