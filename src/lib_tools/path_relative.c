/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_relative.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 06:38:45 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/03 06:38:46 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	char		*free_and_ret(char *path, char *tmp)
{
	ft_memdel((void **)&path);
	return (tmp);
}

static	char		*free_and_keep_on(char *path, char *tmp, char *arg)
{
	ft_memdel((void **)&path);
	return (get_relative_slash(arg, tmp));
}

static	char		*cuted_line_tmp(char *path, char *tmp)
{
	char			*cut;

	if ((cut = ft_strrchr(path, '/')))
	{
		cut[0] = 0;
		ft_memdel((void **)&tmp);
		tmp = (ft_strlen(path) > 0) ? ft_strdup(path) : ft_strdup("/");
		cut[0] = '/';
	}
	return (tmp);
}

static char			*relative_path_4(char *arg, char *path, char *tmp)
{
	if (ft_strrchr(path, '/'))
	{
		tmp = cuted_line_tmp(path, tmp);
		return (free_and_keep_on(path, tmp, &arg[3]));
	}
	return (free_and_ret(path, tmp));
}

char				*get_relative_slash(char *arg, char *path)
{
	char			*tmp;

	if (!path)
		return (NULL);
	tmp = ft_strdup(path);
	if (!arg || !ft_strlen(arg) || !ft_strcmp(path, "/"))
		return (free_and_ret(path, tmp));
	else if (is_relative_path(arg) == 1)
		return (free_and_ret(path, tmp));
	else if (is_relative_path(arg) == 2)
	{
		tmp = cuted_line_tmp(path, tmp);
		return (free_and_ret(path, tmp));
	}
	if (is_relative_path(arg) == 3)
		return (free_and_keep_on(path, tmp, &arg[2]));
	if (is_relative_path(arg) == 4)
		return (relative_path_4(arg, path, tmp));
	return (NULL);
}
