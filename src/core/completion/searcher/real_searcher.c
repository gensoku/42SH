/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_searcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 04:50:18 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/25 04:50:20 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int			search_check_err(t_env *e, char **last_arg, int i)
{
	size_t			len;

	len = ft_strlen(e->line);
	if (!e->line || !len || !(*last_arg = ft_strtrim(e->line)))
		return (get_cur_free(NULL, NULL, NULL));
	if (ft_strlen(*last_arg) == 0)
		return (get_cur_free(last_arg, NULL, NULL));
	ft_memdel((void **)last_arg);
	if (e->line[len - 1] == ' ' && check_back_from(e->line,
		len - 1) % 2 == 0)
	{
		*last_arg = ft_strdup(e->line);
		return (get_cur_free(last_arg, NULL, NULL));
	}
	*last_arg = get_last_arg(e->line);
	if (!(i = get_type_search(e->line)))
	{
		ft_memdel((void **)last_arg);
		return (-1);
	}
	if (!(*last_arg))
		return (-1);
	return (i);
}

int					dir_spoted(t_env *e, char **path,
	char **last_arg, t_comp *list)
{
	char			*tmp;

	tmp = ft_strdup(e->line);
	ft_memdel((void **)&e->line);
	e->line = add_slash_free(tmp, 1);
	list = get_dir_with_opts(CONTEXT, NULL, *last_arg,
		GET_DIR_PATH | GET_FULL_DIR);
	return (ret_sch_free(e, list, last_arg, path));
}

int					searcher(t_env *e, int i)
{
	char			*last_arg;
	char			**arr;
	int				ret;
	t_comp			*list;

	last_arg = NULL;
	list = NULL;
	if ((i = search_check_err(e, &last_arg, 0)) == -1)
		return (-1);
	if (i == 1)
	{
		if (!(list = get_exe_all(last_arg, e)))
			return (first_case_no_exe(e, &last_arg));
		arr = ft_strsplit_spec(e->line, 1);
		ret = return_search(e, NULL, list, arr);
		(arr) ? ft_del_tab(arr) : 0;
		ft_memdel((void **)&last_arg);
		return (ret);
	}
	else
		return (search_second_case(e, &last_arg));
}
