/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 05:44:34 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 04:51:21 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

char				*get_env_line(char **array, char *line)
{
	char			*ret;
	int				i;
	int				len;

	if (!array || !line)
		return (NULL);
	ret = NULL;
	i = -1;
	len = ft_strlen(line);
	while (array[++i])
	{
		if (!ft_strncmp(array[i], line, len))
			return (ft_strdup(array[i]));
	}
	return (ret);
}
