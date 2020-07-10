/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history__hentries.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:48:37 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/12 10:48:41 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

t_hentries			*built_history__hentries_add(t_history *history,
	t_hentries *entry)
{
	t_hentries		*end;

	if (history->entries)
	{
		end = built_history__hentries_end(history->entries);
		entry->id = end->id + 1;
		built_history__hentries_end(history->entries)->next = entry;
		history->total = entry->id;
	}
	else
	{
		entry->id = 1;
		history->entries = entry;
		history->total = entry->id;
	}
	return (entry);
}

t_hentries			*built_history__hentries_end(t_hentries *entries)
{
	t_hentries		*tmp;

	tmp = entries;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_hentries			*built_history__hentries_new(void)
{
	t_hentries		*new;

	if (!(new = (t_hentries *)malloc(sizeof(t_hentries))))
		return (NULL);
	new->id = 0;
	new->time = NULL;
	new->state = NULL;
	new->cmd = NULL;
	new->next = NULL;
	return (new);
}
