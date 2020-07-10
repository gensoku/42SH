/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back_comp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 09:45:16 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:48:02 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

t_comp		*add_comp_ex_(t_comp *node, t_comp *lst)
{
	if (!node)
		return (lst);
	lst = push_back_comp(node->name, lst, node->type);
	ft_memdel((void **)&node->name);
	node->type = 0;
	ft_memdel((void **)&node);
	return (lst);
}

t_comp		*push_back_comp(char *name, t_comp *lst, int type)
{
	t_comp *node;
	t_comp *tmp;

	node = NULL;
	if (!name)
		return (lst);
	if ((node = (t_comp *)malloc(sizeof(t_comp))) == NULL)
		display_error(-1, "malloc failed t_comp *, exit", get_e(NULL));
	node->next = NULL;
	node->name = add_backslash(name, type, -1);
	node->type = type;
	tmp = lst;
	if (!tmp)
		return (node);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (lst);
}
