/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_one_no_exe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 04:13:05 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/19 04:13:07 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int			ret_sch_free(t_env *e, t_comp *list, char **last_arg, char **path)
{
	char	**tools;

	tools = NULL;
	tools = ft_strsplit_spec(e->line, 1);
	return_search(e, NULL, list, tools);
	ft_del_tab(tools);
	ft_memdel((void **)last_arg);
	ft_memdel((void **)path);
	return (0);
}

int			set_free_ret(char **last_arg, char **path, t_comp *list, t_env *e)
{
	char	**tmp;

	e->line = add_slash_free(e->line, 1);
	tmp = ft_strsplit_spec(e->line, 1);
	return_search(e, NULL, list, tmp);
	ft_del_tab(tmp);
	ft_memdel((void **)last_arg);
	ft_memdel((void **)path);
	return (0);
}

static int	loc_or_cmp(t_env *e, char **last_arg, char **path, t_comp *list)
{
	char	*to_cmp;
	char	*cut;
	char	char_save;

	cut = ft_strrchr(*last_arg, '/');
	to_cmp = cut ? ft_strdup(&cut[1]) : ft_strdup(*last_arg);
	if (cut)
	{
		char_save = cut[1];
		cut[1] = 0;
		*path = ft_strdup(*last_arg);
		cut[1] = char_save;
	}
	!cut ? *path = ft_strdup("./") : 0;
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
	return (ret_sch_free(e, list, last_arg, path));
}

int			absolute_p(t_env *e, char **last_arg, t_comp *list, char **path)
{
	char	*cut;
	char	char_save;

	*last_arg = add_slash_free(*last_arg, 1);
	if (g_sts_f(*last_arg, F_GET_TYPE) == F_DIR)
		return (dir_spoted(e, path, last_arg, list));
	else
	{
		ft_memdel((void **)last_arg);
		*last_arg = get_last_arg(e->line);
		cut = ft_strrchr(*last_arg, '/');
		if (cut)
		{
			char_save = cut[1];
			cut[1] = 0;
			*path = ft_strdup(*last_arg);
			cut[1] = char_save;
			if (g_sts_f(*path, F_GET_TYPE) == F_DIR)
				return (dir_spoted(e, path, last_arg, list));
		}
	}
	return (ret_sch_free(e, list, last_arg, path));
}

int			first_case_no_exe(t_env *e, char **last_arg)
{
	char	*path;

	path = (cls(*last_arg)) ? get_back_path_link(e, *last_arg) : NULL;
	if ((g_sts_f(path ? path : *last_arg, F_GET_TYPE) == F_DIR))
		return (dir_spoted(e, &path, last_arg, NULL));
	else if (*last_arg[0] == '/')
		return (absolute_p(e, last_arg, NULL, &path));
	else
	{
		(path) ? ft_memdel((void **)&path) : 0;
		return (loc_or_cmp(e, last_arg, &path, NULL));
	}
}
