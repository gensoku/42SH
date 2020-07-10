/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_set_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 10:53:56 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:49:01 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	t_lst_av			*push_back(t_lst_av *lst, t_lst_av *node)
{
	t_lst_av		*tmp;

	tmp = lst;
	while (tmp->next && tmp->next->current != 1)
		tmp = tmp->next;
	node->next = lst;
	node->previous = tmp;
	tmp->next = node;
	lst->previous = node;
	return (lst);
}

static	t_lst_av			*adv_aa_2(int i, t_lst_av *node, t_lst_av *lst)
{
	if (i == 1)
	{
		node->current = 1;
		node->previous = node;
		node->next = node;
		return (node);
	}
	else
	{
		node->current = 0;
		return (push_back(lst, node));
	}
}

t_lst_av					*set_list(t_comp *path)
{
	int				i;
	t_lst_av		*lst;
	t_lst_av		*node;
	t_comp			*tmp;

	i = 1;
	tmp = path;
	lst = NULL;
	node = NULL;
	while (tmp)
	{
		if ((node = (t_lst_av *)malloc(sizeof(t_lst_av))) == NULL)
			display_error(-1, "malloc failed t_lst_av, exit", get_e(NULL));
		node->name = ft_strdup(tmp->name);
		node->selected = 0;
		lst = adv_aa_2(i, node, lst);
		i++;
		tmp = tmp->next;
	}
	return (lst);
}
