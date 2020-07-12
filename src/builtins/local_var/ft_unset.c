/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:47:39 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static char				*is_a_tab_part(char *key, char *to_cmp)
{
	int					i;
	int					j;
	char				*ret;

	i = ft_strlen(key);
	if (!key || !to_cmp || ft_strncmp(key, to_cmp, i))
		return (NULL);
	j = 1;
	ret = NULL;
	if (to_cmp[i] && to_cmp[i] == '[')
	{
		if (to_cmp[i + j])
		{
			while (to_cmp[i + j] && ft_isdigit(to_cmp[i + j]))
				j++;
			if (to_cmp[i + j] && to_cmp[i + j] == ']')
				if (!to_cmp[i + j + 1])
					return ((ret = ft_strdup(to_cmp)));
		}
	}
	return (NULL);
}

static char				*get_key_tab(char *key, t_env *e)
{
	t_loc_var			*list;
	char				*tmp;

	if (!key)
		return (NULL);
	list = e->all_var;
	tmp = NULL;
	while (list)
	{
		if (list->key && !ft_strcmp(key, list->key))
			return ((tmp = ft_strdup(key)));
		else if (list->key && !ft_strncmp(key, list->key, ft_strlen(key)))
		{
			if ((tmp = is_a_tab_part(key, list->key)))
				return (tmp);
		}
		list = list->next;
	}
	return (NULL);
}

static int				remove_var_or_tab(char *key, t_env *e)
{
	static char			*array[3] = {"unsetenv", 0, 0};
	char				*tmp;
	int					ret;

	ret = 0;
	while (remove_var((tmp = get_key_tab(key, e))))
	{
		array[1] = tmp;
		ft_unsetenv(array, e);
		ft_memdel((void **)&tmp);
		ret++;
	}
	return (ret);
}

void					ft_unset(char **arg, t_env *e)
{
	unsigned long		opts;
	int					i;

	opts = 0;
	if (!arg)
		return ;
	i = 1;
	if (arg[i] && check_opts(arg[i], "f", &opts, SET_OPTS))
		i++;
	if (!arg[i])
		ft_putendl_fd("unset : no enough arguments.", 2);
	while (arg[i] && ft_strlen(arg[i]))
	{
		if (!remove_var_or_tab(arg[i], e))
		{
			ft_putstr_fd("Error unables to unset : ", 2);
			ft_putendl_fd(arg[i], 2);
		}
		i++;
	}
}
