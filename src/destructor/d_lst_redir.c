/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_lst_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:17 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			del_list_redir(t_env *e)
{
	t_redir *tmp;
	t_redir *tmp2;

	tmp = e->left_redir;
	while (tmp)
	{
		if (tmp->token)
		{
			free(tmp->token);
			tmp->token = NULL;
		}
		if (tmp->path)
		{
			free(tmp->path);
			tmp->path = NULL;
		}
		tmp2 = tmp->next;
		free(tmp);
		tmp = NULL;
		tmp = tmp2;
		tmp2 = NULL;
	}
	e->left_redir = NULL;
}
