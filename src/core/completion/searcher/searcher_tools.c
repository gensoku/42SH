/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 07:59:09 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/16 07:59:10 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		set_env_comp(t_env *e, t_comp *list)
{
	(e->comp_path) ? del_t_comp(e->comp_path) : (void)e->comp_path;
	e->comp_path = NULL;
	e->comp_exe = NULL;
	e->comp_path = list;
	e->comp_exe = list;
	return (0);
}

static	void	set_search_line(t_env *e, t_comp *list, char **last_arg)
{
	ft_memdel((void **)&e->line);
	if (last_arg && *last_arg)
		e->line = ft_strnew(ft_strlen(*last_arg) + 1 + ((list) ?
			ft_strlen(list->name) : 0));
	else
		e->line = ft_strnew(ft_strlen(list->name) + 1);
	(last_arg && *last_arg) ? ft_strcat(e->line, *last_arg) : 0;
	list ? ft_strcat(e->line, " ") : 0;
	list ? ft_strcat(e->line, list->name) : 0;
	ft_memdel((void **)last_arg);
}

int				return_search(t_env *e, char **last_arg, t_comp *list,
	char **tab_args)
{
	char		*implode;
	size_t		len;

	if (!tab_args && ((last_arg && *last_arg) || list))
		set_search_line(e, list, last_arg);
	else if (tab_args)
	{
		implode = ft_implode(tab_args, ' ');
		len = ft_strlen(implode);
		len += (list) ? ft_strlen(list->name) : 0;
		len += 2;
		ft_memdel((void **)&e->line);
		e->line = ft_strnew(len);
		ft_strcat(e->line, implode);
		list ? ft_strcat(e->line, list->name) : 0;
		ft_memdel((void **)&implode);
	}
	return (set_env_comp(e, list));
}

int				get_cur_free(char **last_arg, char **line, t_comp *list)
{
	ft_memdel((void **)line);
	list = get_dir_with_opts(CONTEXT, NULL, "./", GET_FULL_DIR);
	return_search(CONTEXT, last_arg, list, NULL);
	ft_memdel((void **)last_arg);
	return (-1);
}

char			*add_slash_free(char *line, int opts)
{
	char		*new_line;

	if (!line)
		return (NULL);
	new_line = NULL;
	if (line[ft_strlen(line) - 1] != '/' || (ft_strlen(line) > 1 &&
		check_back_from(line, ft_strlen(line) - 2) % 2 == 1))
	{
		new_line = ft_strnew(ft_strlen(line) + 2);
		ft_strcat(new_line, line);
		ft_strcat(new_line, "/");
		if (opts)
			ft_memdel((void **)&line);
	}
	else
	{
		new_line = ft_strdup(line);
		(opts) ? ft_memdel((void **)&line) : 0;
	}
	return (new_line);
}
