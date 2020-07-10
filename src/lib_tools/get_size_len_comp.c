/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_len_comp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:01:58 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int					get_size_len(char **tab1)
{
	size_t	x;
	int		i;

	x = 0;
	i = 0;
	if (!tab1)
		return (0);
	while (tab1[i])
	{
		if (x < ft_strlen(tab1[i]))
			x = ft_strlen(tab1[i]);
		i++;
	}
	x += 6;
	return (x);
}
