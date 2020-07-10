/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_tmp_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:41 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		del_tmp_env(t_env *e)
{
	t_tmp_env	*tmp;
	t_tmp_env	*tmp2;

	if (!e->tmp_env)
		return ;
	tmp = e->tmp_env;
	tmp2 = tmp;
	while (tmp2)
	{
		if (tmp->value)
			ft_memdel((void**)&(tmp->value));
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	tmp = NULL;
	tmp2 = NULL;
	e->tmp_env = NULL;
}
