/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_enter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:48:52 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static char	*norm_enter(char *ret, t_lst_av *tmp)
{
	char *tmp_char;

	tmp_char = ft_strdup(ret);
	free(ret);
	ret = ft_strjoin(tmp_char, " ");
	free(tmp_char);
	tmp_char = ft_strjoin(ret, tmp->name);
	free(ret);
	ret = ft_strdup(tmp_char);
	free(tmp_char);
	tmp_char = NULL;
	return (ret);
}

void		enter(t_env *e)
{
	t_lst_av	*tmp;
	int			z;
	char		*ret;

	tmp = e->cur_node;
	z = 0;
	ret = NULL;
	if (tmp)
	{
		while (tmp->current != 1 || z == 0)
		{
			if (tmp->selected == 1)
			{
				if (!ret)
					ret = ft_strdup(tmp->name);
				else
					ret = norm_enter(ret, tmp);
			}
			tmp = tmp->next;
			z++;
		}
	}
	e->ret_comp = ret;
	e->stop_comp = 1;
}
