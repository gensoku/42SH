/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:48:06 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			push_back_redir(t_env *e, char *token, char *path)
{
	t_redir *node;
	t_redir *tmp;

	tmp = e->left_redir;
	if ((node = (t_redir*)malloc(sizeof(t_redir) * 1)) == NULL)
		display_error(-1, "malloc failed t_redir, exit", CONTEXT);
	node->next = NULL;
	node->path = ft_strdup(path);
	node->token = ft_strdup(token);
	if (!tmp)
		e->left_redir = node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}
