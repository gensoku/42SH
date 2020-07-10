/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check_is_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:47:09 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int				is_var_(char *key)
{
	t_loc_var	*tmp;

	tmp = CTX(all_var);
	if (!key)
		return (0);
	while (tmp)
	{
		if (tmp->key && !ft_strcmp(key, tmp->key))
			return (tmp->type);
		tmp = tmp->next;
	}
	return (0);
}
