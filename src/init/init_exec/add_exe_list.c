/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exe_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 06:28:29 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static t_exe	*push_back_exe(t_exe *e, char *path, char *name)
{
	t_exe	*tmp;
	t_exe	*node;
	char	*name_tmp;

	if (!path || !name)
		return (NULL);
	if ((node = (t_exe*)malloc(sizeof(t_exe))) == NULL)
		display_error(-1, "malloc failed t_exe *, exit", get_e(NULL));
	node->name = ft_strdup(name);
	node->path = ft_strdup(path);
	node->full_name = ft_strjoin(path, "/");
	name_tmp = ft_strjoin(node->full_name, name);
	free(node->full_name);
	node->full_name = name_tmp;
	node->next = NULL;
	tmp = e;
	if (!tmp)
		return (node);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (e);
}

static void		check_path_full(char *path, char *full_path, int len)
{
	if (!path || !full_path || !len)
		return ;
	if (path && len != 0)
	{
		if (path[len - 1] && path[len - 1] != '/')
			ft_strcat(full_path, "/");
		else if (len > 1 && check_back_from(path, len - 2) % 2 != 0)
			ft_strcat(full_path, "/");
	}
}

static t_exe	*add_exe_lst(char *path)
{
	DIR				*dir;
	t_exe			*tmp;
	char			*full_path;
	struct dirent	*entry;
	int				len;

	tmp = NULL;
	if ((dir = opendir(path)) == NULL)
		return (NULL);
	full_path = NULL;
	len = ft_strlen(path);
	while ((entry = readdir(dir)) != NULL)
	{
		full_path = ft_strnew(ft_strlen(path) + ft_strlen(entry->d_name) + 2);
		ft_strcat(full_path, path);
		check_path_full(path, full_path, len);
		ft_strcat(full_path, entry->d_name);
		if (ft_is_point(entry->d_name) == 0 && (g_sts_f(full_path,
			F_GET_TYPE) == F_REG || (g_sts_f(full_path, F_GET_TYPE) ==
				F_SYMLINK && g_sts_f(full_path, F_GETLNK_TYPE) == F_REG)))
			tmp = push_back_exe(tmp, path, entry->d_name);
		ft_memdel((void **)&full_path);
	}
	closedir(dir);
	return (tmp);
}

t_spath			*add_exe(t_spath *lst, char *path)
{
	t_spath	*node;
	t_spath	*tmp;

	if (!path)
		return (NULL);
	if ((node = (t_spath*)malloc(sizeof(t_spath))) == NULL)
		display_error(-1, "malloc failed t_spath *, exit", get_e(NULL));
	node->name = ft_strdup(path);
	node->next = NULL;
	node->list = add_exe_lst(path);
	if (!node->list)
	{
		(node->name) ? ft_memdel((void**)&(node->name)) : (void)tmp;
		ft_memdel((void**)&node);
	}
	if (!lst)
		return (node);
	else
	{
		tmp = lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (lst);
}
