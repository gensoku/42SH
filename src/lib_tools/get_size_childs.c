/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_childs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 10:58:19 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:01:56 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int				get_size_childs(t_childs *childs)
{
	t_childs	*tmp;
	int			i;

	tmp = childs;
	i = 0;
	if (tmp)
	{
		while (tmp)
		{
			i++;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}
