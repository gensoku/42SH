/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 04:34:05 by tsedigi           #+#    #+#             */
/*   Updated: 2017/04/06 04:34:06 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		del_history(t_history **h)
{
	t_history	*t;
	t_hentries	*tmp;
	t_hentries	*tmp2;

	if (!h || !*h)
		return ;
	t = *h;
	tmp = t->entries;
	tmp2 = tmp;
	ft_memdel((void **)&t->raw);
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_memdel((void **)&tmp->time);
		ft_memdel((void **)&tmp->state);
		ft_memdel((void **)&tmp->cmd);
		ft_memdel((void **)&tmp);
		tmp = tmp2;
	}
	ft_memdel((void **)h);
}
