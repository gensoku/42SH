/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_jobs_setters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 03:36:09 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:43:59 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			jobs_setter__reset(t_childs *tmp, int jump)
{
	if (!tmp)
		return ;
	if (jump)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->last == 1)
			tmp->last = 0;
		else if (tmp->last == 0)
			tmp->last = -1;
		tmp = tmp->next;
	}
}

t_childs		*jobs_setter__last(t_childs *tmp, pid_t pid)
{
	t_childs	*tmp2;

	tmp2 = jobs_getter__bypid(pid, CONTEXT);
	if (!tmp2)
		return (NULL);
	if (tmp2->last == 1)
		return (tmp2);
	else
	{
		jobs_setter__reset(tmp, 0);
		tmp2->last = 1;
	}
	if (tmp2)
		return (tmp2);
	else
		return (NULL);
}

static	void	jobs_setter__upgr_t1(t_childs *head)
{
	if (!head->next)
		head->last = 1;
	else if (head->last == 0)
	{
		head->last = 1;
		head->next->last = 0;
		return ;
	}
	while (head->next)
	{
		if (head->next->last == 0)
		{
			head->next->last = 1;
			if (head->next->next)
				head->next->next->last = 0;
			else
				head->last = 0;
			break ;
		}
		head = head->next;
	}
}

static	void	jobs_setter__upgr_t0(t_childs *head)
{
	if (!head->next)
		return ;
	else if (head->last == 1)
	{
		head->next->last = 0;
		return ;
	}
	while (head->next)
	{
		if (head->next->last == 1)
		{
			if (head->next->next)
				head->next->next->last = 0;
			else
				head->last = 0;
			return ;
		}
		head = head->next;
	}
}

void			jobs_setter__upgr(t_childs *head, int type)
{
	if (!head)
		return ;
	if (type == 1)
		jobs_setter__upgr_t1(head);
	else if (type == 0)
		jobs_setter__upgr_t0(head);
}
