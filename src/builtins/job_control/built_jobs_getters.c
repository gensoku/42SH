/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_jobs_getters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 00:17:55 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/12 10:26:54 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

t_childs				*jobs_getter__bylast(t_childs *head, int type)
{
	if (!head)
		return (NULL);
	while (head)
	{
		if (type == 1 && head->last == 1)
			return (head);
		else if (type == 0 && head->last == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_childs				*jobs_getter__bypid(pid_t pid, t_env *e)
{
	t_childs			*tmp;

	tmp = e->childs;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (tmp->child == pid)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_childs				*jobs_getter__bypgid(pid_t pgid, t_env *e)
{
	t_childs			*tmp;

	tmp = e->childs;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (tmp->grpid == pgid)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
