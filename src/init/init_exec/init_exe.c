/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 06:44:12 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static t_spath	*set_exe_path(t_env *e, int i, int j, int k)
{
	char		*path2;
	char		*path;
	t_spath		*lst;

	path2 = get_env("PATH", e->env, 1);
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
		path = (j == 0) ? ft_strsub(path2, k, ft_strlen(&path2[k]))
		: ft_strsub(path2, i - j, j);
		lst = add_exe(lst, path);
		path ? ft_memdel((void**)&path) : (int)i;
	}
	path2 ? ft_memdel((void**)&path2) : (int)i;
	return (lst);
}

static void		cmp_cat_exe(t_spath *tmp, t_env *e)
{
	t_spath	*tmp2;
	int		flag;

	flag = 0;
	while (tmp)
	{
		tmp2 = e->paths;
		while (tmp2)
		{
			if (ft_strcmp(tmp->name, tmp2->name) == 0)
			{
				flag = 1;
				break ;
			}
			tmp2 = tmp2->next;
		}
		if (flag == 0)
			add_exe(e->paths, tmp->name);
		flag = 0;
		tmp = tmp->next;
	}
	del_t_spath(tmp);
}

void			set_exe(t_env *e)
{
	char	*path;
	t_spath	*tmp;

	path = get_env("PATH", e->env, 1);
	if (!e->paths && path)
		e->paths = set_exe_path(e, 0, 0, 0);
	else if (e->paths && path)
	{
		tmp = set_exe_path(e, 0, 0, 0);
		cmp_cat_exe(tmp, e);
		del_t_spath(tmp);
	}
	path ? ft_memdel((void**)&path) : (void)path;
	set_hash(e);
}
