/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 10:44:13 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:01:41 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int		ft_is_point(char *str)
{
	if (!str)
		return (1);
	if (ft_strlen(str) == 1 && str[0] == '.')
		return (1);
	else if (ft_strlen(str) == 2 && str[0] == '.' && str[1] == '.')
		return (1);
	return (0);
}
