/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_setting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:49:04 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int				get_size_len_comp(t_comp *path)
{
	size_t				x;
	t_comp				*tmp;

	x = 0;
	if (!path)
		return (0);
	tmp = path;
	while (tmp)
	{
		if (x < ft_strlen(tmp->name))
			x = ft_strlen(tmp->name);
		tmp = tmp->next;
	}
	if (x > 0)
		x += 6;
	return (x);
}

static	int				ft_size_list(t_comp *exe)
{
	t_comp				*tmp;
	int					max;

	tmp = exe;
	max = 0;
	while (tmp)
	{
		max++;
		tmp = tmp->next;
	}
	return (max);
}

static	int				norm_ret_del_(t_env *e)
{
	del_list_av(e);
	return (-1);
}

int						auto_comp(t_env *e)
{
	t_cursor			all;
	int					size;
	int					mod;

	mod = 0;
	size = 0;
	if (!e->line || !e->comp_path)
		return (-2);
	if (e->auto_c)
		del_list_av(e);
	e->auto_c = set_list(e->comp_path);
	e->cur_node = e->auto_c;
	size = ft_size_list(e->comp_path);
	all.col = get_size_len_comp(e->comp_path);
	all.total = (e->col / all.col);
	mod = size % all.total;
	all.row = size / all.total;
	all.row = (mod != 0) ? all.row + 1 : all.row;
	all.total = (all.total > size) ? size : all.total;
	if (e->col < all.col || all.row >= e->row / 2)
		return (norm_ret_del_(e));
	get_inter(e, &all);
	del_list_av(e);
	return (0);
}
