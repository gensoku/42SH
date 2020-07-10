/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_stats.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 07:13:26 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int		g_sts_f(char *path, int type)
{
	struct stat sts;

	if (!path)
		return (0);
	if (type == F_GETLNK_TYPE)
	{
		if (stat(path, &sts) == -1)
			return (0);
		else
			return (typedefineargs(sts.st_mode));
	}
	if (lstat(path, &sts) != -1)
	{
		if (type == F_GET_TYPE)
			return (typedefineargs(sts.st_mode));
		else if (type == F_GET_NLNK)
			return ((int)sts.st_nlink);
	}
	return (0);
}
