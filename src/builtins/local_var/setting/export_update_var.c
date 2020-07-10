/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:47:32 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int				update_var(char *key, char *val, t_env *e)
{
	t_loc_var	*tmp;

	if (!(tmp = get_var_ptr(e, key, 1)))
		return (0);
	(tmp->value) ? free(tmp->value) : 0;
	tmp->value = ft_strdup(val);
	return (1);
}
