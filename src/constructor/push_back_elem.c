/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 08:43:00 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:48:04 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

t_comp	*push_back_elem_(char *str, t_comp *list, int typed)
{
	t_comp *node;
	t_comp *tmp;

	if (!str || ft_strlen(str) == 0)
		return (list);
	if ((node = (t_comp *)malloc(sizeof(t_comp))) == NULL)
		display_error(-1, "malloc failed t_comp, exit", CONTEXT);
	node->name = ft_strdup(str);
	node->next = NULL;
	node->type = typed;
	if (!list)
		return (node);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (list);
}
