/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_p.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 05:08:31 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 07:48:48 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void		print_helper_p(t_env *e, char *name)
{
	ft_putstr_fd("#env Searching: ", 2);
	ft_putendl_fd(e->alt_path_line, 2);
	ft_putstr_fd("#env  for file: ", 2);
	ft_putendl_fd(name, 2);
}

static	t_exe		*get_exe_env_p(char *name, t_env *e)
{
	t_exe			*tmp;
	t_spath			*tmp2;

	tmp2 = e->alternate_paths;
	if (!tmp2)
		return (NULL);
	if (verbose_lvl(VERB_VAL) > 1)
		print_helper_p(e, name);
	while (tmp2)
	{
		tmp = tmp2->list;
		while (tmp && tmp->name && name)
		{
			if (ft_strcmp(tmp->name, name) == 0)
			{
				(verbose_lvl(VERB_VAL) > 1) ?
					ft_putstr_fd("#env  matched: ", 2) : 0;
				(verbose_lvl(VERB_VAL) > 1) ? ft_putendl_fd(tmp2->name, 2) : 0;
				return (tmp);
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (NULL);
}

t_exe				*get_exe_alt_paths(char *name, t_env *e)
{
	if (!name || !e)
		return (NULL);
	return (get_exe_env_p(name, e));
}

static	t_spath		*set_exe_path_env(int k, int i, int j, char *path2)
{
	char			*path;
	t_spath			*lst;

	lst = NULL;
	path = NULL;
	while (path2 && path2[i])
	{
		j = 0;
		k = i;
		while (path2[i] && path2[i] != '/' && path2[i] != '.')
			i++;
		while (path2[i] && path2[i] != ':')
		{
			i++;
			j++;
		}
		path = (j == 0) ? ft_strsub(path2, k, ft_strlen(&path2[k])) :
			ft_strsub(path2, i - j, j);
		lst = add_exe(lst, path);
		path ? ft_memdel((void**)&path) : 0;
	}
	return (lst);
}

int					env_opt_p(t_env *e, char *str, unsigned long *opts)
{
	if (!str || !ft_strlen(str))
		return (1);
	(void)opts;
	ft_memdel((void **)&e->alt_path_line);
	e->alt_path_line = ft_strdup(str);
	e->alternate_paths = set_exe_path_env(0, 0, 0, str);
	return (0);
}
