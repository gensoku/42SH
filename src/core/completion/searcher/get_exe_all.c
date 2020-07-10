/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exe_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 10:49:37 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:49:22 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

t_comp	*get_exe_all(char *name, t_env *e)
{
	t_spath	*tmp;
	t_exe	*tmp2;
	t_comp	*list;

	if (!name || ft_strlen(name) == 0)
		return (NULL);
	tmp = e->paths;
	list = NULL;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		tmp2 = tmp->list;
		while (tmp2)
		{
			if (ft_strncmp(name, tmp2->name, ft_strlen(name)) == 0)
				list = push_back_comp(tmp2->name, list, 0);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (list);
}
