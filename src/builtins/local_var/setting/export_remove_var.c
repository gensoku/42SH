/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_remove_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:47:25 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int				remove_var(char *str)
{
	t_loc_var	*tmp;

	if (!str || !(tmp = get_var_ptr(CONTEXT, str, CASE_TRUE)))
		return (0);
	tmp->type = 0;
	tmp->status = 0;
	tmp->empty = 1;
	(tmp->key) ? ft_memdel((void **)&tmp->key) : 0;
	(tmp->value) ? ft_memdel((void **)&tmp->value) : 0;
	return (1);
}
