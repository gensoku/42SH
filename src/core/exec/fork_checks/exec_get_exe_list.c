/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_get_exe_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 05:25:20 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 07:49:30 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

t_exe		*get_exe_hash(char *name, t_env *e)
{
	size_t	i;
	int		break_error;

	if (e->alt_path_line)
		return (get_exe_alt_paths(name, e));
	if (!e->hash || !e->paths)
		return (NULL);
	i = (int)(do_hash(name, e->hash_size));
	break_error = 0;
	while (e->hash[i] && e->hash[i]->name && i < (e->hash_size * 16))
	{
		if (!ft_strcmp(e->hash[i]->name, name))
			return (e->hash[i]);
		i++;
		if (i == (e->hash_size * 16) && !break_error)
		{
			i = 0;
			break_error = 1;
		}
	}
	return (get_exe_list(name, e));
}

t_exe		*get_exe_list(char *name, t_env *e)
{
	t_exe	*tmp;
	t_spath *tmp2;

	tmp2 = e->paths;
	while (tmp2)
	{
		tmp = tmp2->list;
		while (tmp && tmp->name && name)
		{
			if (ft_strcmp(tmp->name, name) == 0)
				return (tmp);
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (NULL);
}
