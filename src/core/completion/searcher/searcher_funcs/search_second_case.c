/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_second_case.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 04:45:06 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/19 04:45:07 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int	find_from_list(t_env *e, t_comp *list, char **last_arg, char **path)
{
	if (!list)
	{
		ft_memdel((void **)last_arg);
		*last_arg = get_last_arg(e->line);
		list = get_exe_all(*last_arg, e);
		ft_memdel((void **)last_arg);
	}
	return (ret_sch_free(e, list, last_arg, path));
}

static char	*find_good_path(char *cut, char **last_arg)
{
	char	char_save;
	char	*ret;

	if (cut)
	{
		char_save = cut[1];
		cut[1] = 0;
		ret = ft_strdup(*last_arg);
		cut[1] = char_save;
	}
	else
		ret = ft_strdup("./");
	return (ret);
}

static int	loc_cmp_exe(t_env *e, char **last_arg, char **path, t_comp *list)
{
	char	*to_cmp;
	char	*cut;

	cut = ft_strrchr(*last_arg, '/');
	to_cmp = cut ? ft_strdup(&cut[1]) : ft_strdup(*last_arg);
	*path = find_good_path(cut, last_arg);
	if (to_cmp && g_sts_f(*path, F_GET_TYPE) == F_DIR)
	{
		if ((list = get_dir_with_opts(CONTEXT, to_cmp, *path,
			cut ? GET_DIR_PATH : 0)))
		{
			ft_memdel((void **)&to_cmp);
			return (set_free_ret(last_arg, path, list, e));
		}
	}
	ft_memdel((void **)&to_cmp);
	return (find_from_list(e, list, last_arg, path));
}

int			search_second_case(t_env *e, char **last_arg)
{
	char	*path;

	path = NULL;
	if ((g_sts_f(*last_arg, F_GET_TYPE) == F_DIR))
		return (dir_spoted(e, &path, last_arg, NULL));
	else if (*last_arg[0] == '/')
		return (absolute_p(e, last_arg, NULL, &path));
	else
		return (loc_cmp_exe(e, last_arg, &path, NULL));
}
