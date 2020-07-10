/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:59 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static char			**ft_list_to_tab1(t_comp *exe, int max)
{
	char			**ret;
	int				x;
	t_comp			*tmp;

	x = 0;
	if (max == 0)
		return (NULL);
	if ((ret = (char **)ft_memalloc(sizeof(char *) * max + 1)) == NULL)
		ft_putstr_fd("malloc failed () exit.\n", 2);
	tmp = exe;
	while (tmp)
	{
		if (tmp->name && ft_strlen(tmp->name) > 0)
		{
			ret[x] = ft_strdup(tmp->name);
			x++;
		}
		tmp = tmp->next;
	}
	ret[x] = 0;
	return (ret);
}

static int			ft_size_list(t_comp *exe)
{
	t_comp			*tmp;
	int				max;

	tmp = exe;
	max = 0;
	while (tmp)
	{
		max++;
		tmp = tmp->next;
	}
	return (max);
}

void				display_col(t_comp *exe, t_env *e)
{
	char			**tab1;
	int				size;

	tab1 = NULL;
	size = 0;
	if (!exe)
		return ;
	size = ft_size_list(exe);
	tab1 = ft_list_to_tab1(exe, size);
	if (!tab1 || size == 0)
		return ;
	display_all(tab1, e, size, 0);
	if (tab1)
		ft_del_tab(tab1);
	tab1 = NULL;
}
