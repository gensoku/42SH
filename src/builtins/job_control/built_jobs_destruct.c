/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_jobs_destruct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 04:38:06 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:54:57 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void		remove_last_jobs(t_childs *tmp, t_childs *job)
{
	while (tmp)
	{
		if (tmp->next && tmp->next->child == job->child)
		{
			tmp->next = job->next;
			break ;
		}
		tmp = tmp->next;
	}
}

void				jobs_destruct__bypid(pid_t pid, t_env *e)
{
	t_childs		*job;
	t_childs		*tmp;
	int				save;

	job = jobs_getter__bypid(pid, e);
	tmp = e->childs;
	if (!job)
		return ;
	save = job->last;
	if (tmp == job && tmp->next)
		e->childs = tmp->next;
	else if (tmp == job)
		e->childs = NULL;
	else
		remove_last_jobs(tmp, job);
	jobs_destruct__last(&job);
	job = NULL;
	tmp = e->childs;
	(save == 1) ? jobs_setter__upgr(tmp, 1) : 0;
	(save == 0) ? jobs_setter__upgr(tmp, 0) : 0;
}

void				jobs_destruct__last(t_childs **node)
{
	if (!node || !*node)
		return ;
	((*node)->name) ? ft_memdel((void**)&((*node)->name)) : 0;
	(*node)->status = 0;
	(*node)->child = 0;
	(*node)->last = 0;
	free(*node);
}
