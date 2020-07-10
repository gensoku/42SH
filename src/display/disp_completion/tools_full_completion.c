/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_full_completion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:59:05 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		ft_size_tab1(char **tab1)
{
	int			i;

	i = 0;
	if (!tab1)
		return (0);
	while (tab1 && tab1[i])
		i++;
	return (i);
}

static t_comp	*get_comp_iter(t_comp *lst, int i)
{
	t_comp		*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (i)
	{
		if (tmp)
			tmp = tmp->next;
		else
			return (NULL);
		i--;
	}
	return (tmp);
}

static void		hlp_p_t1_co(char **tab1, int value, int max)
{
	t_comp			*tmp;

	(((tmp = get_comp_iter(CTX(comp_path), value))) &&
		(CTX(color_def) & COL_EN)) ? set_color_type(tmp->type) : 0;
	ft_putstr(tab1[value]);
	ft_putstr(RESET);
	ft_putspace(ft_strlen(tab1[value]), max);
}

static void		print_tab1_col_n(char **tab1, int max, int x_max, int col)
{
	int			x;
	int			i;
	t_comp		*tmp;

	i = 0;
	x = 0;
	tmp = NULL;
	while (x < x_max)
	{
		while (i < col)
		{
			if (x + (i * x_max) < ft_size_tab1(tab1) && x_max > 1)
				hlp_p_t1_co(tab1, (x + (i * x_max)), max);
			else if (x_max == 0 && i < ft_size_tab1(tab1))
				hlp_p_t1_co(tab1, i, max);
			i++;
		}
		ft_putchar('\n');
		x++;
		i = 0;
		(tmp) ? tmp = tmp->next : 0;
	}
}

void			print_tab1_col(char **tab1, int max, int x_max, int col)
{
	int			i;
	t_env		*e;
	t_comp		*tmp;

	i = 0;
	e = get_e(NULL);
	tmp = e->comp_path;
	if (x_max > 1)
		print_tab1_col_n(tab1, max, x_max, col);
	else if (x_max == 1)
	{
		while (i < col && tab1[i])
		{
			(tmp && (e->color_def & COL_EN)) ? set_color_type(tmp->type) : 0;
			ft_putstr(tab1[i]);
			(tmp && (e->color_def & COL_EN)) ? ft_putstr(RESET) : 0;
			ft_putspace(ft_strlen(tab1[i]), max);
			i++;
			(tmp) ? tmp = tmp->next : 0;
		}
		ft_putchar('\n');
	}
}
