/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_current_dir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 10:35:59 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static t_comp		*set_name_with_path(char *path, char *entry,
	char *path2, int opts)
{
	char			*full_name;
	char			*full_name_2;
	char			*tmp;
	t_comp			*node;

	full_name_2 = NULL;
	node = NULL;
	tmp = NULL;
	if (opts & GET_DIR_PATH)
	{
		full_name = ft_strjoin(path, entry);
		tmp = path2 ? ft_strjoin(path2, "/") : NULL;
		full_name_2 = path2 ? ft_strjoin(tmp, entry) : NULL;
	}
	else
		full_name = ft_strdup(entry);
	node = push_back_comp(full_name, node, g_sts_f(full_name_2 ? full_name_2 :
		full_name, F_GET_TYPE));
	ft_memdel((void **)&full_name);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&full_name_2);
	return (node);
}

static t_comp		*setup_free(char **p1, char **p2)
{
	ft_memdel((void **)p1);
	ft_memdel((void **)p2);
	return (NULL);
}

t_comp				*get_dir_with_opts(t_env *e, char *to_cmp,
	char *path, int opts)
{
	DIR				*direc;
	struct dirent	*entry;
	t_comp			*lst;
	char			*path2;
	size_t			size;

	lst = NULL;
	size = ft_strlen(to_cmp);
	path2 = cls(path) ? get_back_path_link(e, path) : NULL;
	path = add_slash_free(path, 0);
	if ((direc = opendir(path2 ? path2 : path)) == NULL)
		return (setup_free(&path, &path2));
	while ((entry = readdir(direc)) != NULL)
	{
		if (!ft_strcmp(entry->d_name, ".") || !ft_strcmp(entry->d_name, ".."))
			continue ;
		if (opts & GET_FULL_DIR && entry->d_name[0] == '.')
			continue ;
		if (opts & GET_FULL_DIR || !ft_strncmp(to_cmp, entry->d_name, size))
			lst = add_comp_ex_(set_name_with_path(path, entry->d_name,
				path2, opts), lst);
	}
	(closedir(direc) == -1) ? display_error(-1, "close failed, exit", e) : 0;
	setup_free(&path, &path2);
	return (lst);
}
