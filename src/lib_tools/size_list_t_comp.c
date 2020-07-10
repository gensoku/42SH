/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_list_t_comp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:02:08 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int	size_list_t_comp(t_comp *lst)
{
	t_comp	*tmp;
	int		ret;

	ret = 0;
	tmp = lst;
	if (!tmp)
		return (0);
	while (tmp)
	{
		tmp = tmp->next;
		ret++;
	}
	return (ret);
}
