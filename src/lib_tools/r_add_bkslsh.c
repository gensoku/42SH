/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_add_bkslsh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 05:14:02 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/28 05:14:04 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		read_add_bkslsh(char **line, char *to_slsh)
{
	char	*ret;
	char	*adds;
	int		i;
	int		j;

	if (!line || !*line || !to_slsh)
		return ;
	ret = ft_strnew(ft_strlen(*line) * 2 + 1);
	adds = *line;
	i = 0;
	j = 0;
	while (adds[i])
	{
		if (ft_strchr(to_slsh, adds[i]))
		{
			ret[j] = '\\';
			j++;
		}
		ret[j] = adds[i];
		i++;
		j++;
	}
	*line ? free(*line) : 0;
	*line = ret;
}
