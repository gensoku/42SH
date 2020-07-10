/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_reset_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:47:27 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			reset_var(char *str, t_loc_var *setter)
{
	t_loc_var	*tmp;

	if (!str || !setter || !(tmp = get_var_ptr(CONTEXT, str, CASE_TRUE)))
		return ;
	remove_var(str);
	tmp->type = setter->type;
	tmp->status = setter->status;
	tmp->key = (setter->key) ? ft_strdup(setter->key) : NULL;
	tmp->value = (setter->value) ? ft_strdup(setter->value) : NULL;
	(!tmp->key && !tmp->value) ? tmp->empty = 1 : 0;
}
