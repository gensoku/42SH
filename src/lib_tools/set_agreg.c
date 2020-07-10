/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_agreg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:02:06 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		reset_agreg(t_agreg *ag, int opt)
{
	if (!ag)
		return ;
	if (ag->spliter)
		ft_memdel((void**)&(ag->spliter));
	if (ag->left)
		ft_memdel((void **)&(ag->left));
	if (ag->right)
		ft_memdel((void **)&(ag->right));
	if (ag->cut)
		ag->cut = NULL;
	ag->left_val = 0;
	ag->right_val = 0;
	ag->close = 0;
	if (opt)
		free(ag);
}

t_agreg		*set_agreg(void)
{
	t_agreg *t;

	if ((t = (t_agreg*)malloc(sizeof(t_agreg))) == NULL)
		display_error(-1, "Malloc failed , exit", get_e(NULL));
	t->spliter = NULL;
	t->left = NULL;
	t->right = NULL;
	t->cut = NULL;
	t->left_val = 0;
	t->right_val = 0;
	t->close = 0;
	return (t);
}
