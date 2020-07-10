/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_relative_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 08:00:48 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 08:16:15 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int			is_relative_path(char *path)
{
	int		len;

	len = ft_strlen(path);
	if (!path)
		return (0);
	if (len == 1 && path[0] == '.')
		return (1);
	else if (len == 2 && !ft_strcmp(path, ".."))
		return (2);
	else if (!ft_strncmp(path, "./", 2))
		return (3);
	else if (!ft_strncmp(path, "../", 3))
		return (4);
	return (0);
}
