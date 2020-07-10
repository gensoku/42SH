/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_get_var_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:47:22 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

t_loc_var		*get_last_var(void)
{
	t_loc_var	*tmp;

	if (!CTX(all_var))
		return (NULL);
	tmp = CTX(all_var);
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_loc_var		*get_var_ptr(t_env *e, char *key, int sensitive)
{
	t_loc_var	*tmp;
	char		*lower;
	char		*upper;

	if (!key || !(tmp = e->all_var))
		return (NULL);
	upper = !sensitive ? ft_strdup(key) : NULL;
	lower = !sensitive ? ft_strdup(key) : NULL;
	ft_str_tolower(lower);
	ft_str_toupper(upper);
	while (tmp)
	{
		if (tmp->key && (!ft_strcmp(key, tmp->key) || (!sensitive &&
			(!ft_strcmp(lower, tmp->key) || !ft_strcmp(upper, tmp->key)))))
		{
			upper ? ft_memdel((void **)&upper) : 0;
			lower ? ft_memdel((void **)&lower) : 0;
			return (tmp);
		}
		tmp = tmp->next;
	}
	lower ? ft_memdel((void **)&lower) : 0;
	upper ? ft_memdel((void **)&upper) : 0;
	return (NULL);
}
