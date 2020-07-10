/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_all_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 05:05:07 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/28 05:05:12 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			d_all_var(t_loc_var *vars)
{
	t_loc_var	*tmp;
	t_loc_var	*tmp2;

	if (!vars)
		return ;
	tmp = vars;
	tmp2 = NULL;
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_memdel((void **)&tmp->key);
		ft_memdel((void **)&tmp->value);
		tmp->type = 0;
		tmp->status = 0;
		ft_memdel((void **)&tmp);
		tmp = tmp2;
	}
}
