/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_front_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/12 07:04:02 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int									push_front_child_id(t_childs *tmp,
	t_childs *head, int max)
{
	if (!tmp)
		return (max);
	if (tmp->id == max)
		return (push_front_child_id(head, head, max + 1));
	return (push_front_child_id(tmp->next, head, max));
}

t_childs							*push_front_child(pid_t son,
	t_env *e, char *name, int foreground)
{
	t_childs						*node;
	t_childs						*tmp;

	if ((node = (t_childs *)ft_memalloc(sizeof(t_childs))) == NULL)
		display_error(-1, "malloc failed t_child, exit", CONTEXT);
	node->child = son;
	node->name = ft_strdup(name);
	node->foreground = foreground;
	tmp = jobs_getter__bypgid(getpgid(son), e);
	node->id = (tmp && tmp->id) ? tmp->id :
	push_front_child_id(e->childs, e->childs, 1);
	if (e->childs)
		node->next = e->childs;
	else
		node->next = NULL;
	e->childs = node;
	if (foreground)
		jobs_setter__last(e->childs, son);
	else
		node->last = -1;
	return (node);
}
