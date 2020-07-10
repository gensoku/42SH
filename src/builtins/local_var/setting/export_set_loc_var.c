/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_set_loc_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:47:29 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		set_node_local(t_loc_var *node, char *tampon)
{
	char		*cut;

	cut = ft_strchr(tampon, '=');
	if (cut)
	{
		cut[0] = 0;
		node->key = ft_strdup(tampon);
		node->value = (cut[1]) ? ft_strdup(&cut[1]) : NULL;
		cut[0] = '=';
	}
	else
	{
		node->key = ft_strdup(tampon);
		node->value = NULL;
	}
}

void			set_var_(char *line, int type, int status)
{
	t_loc_var	*node;
	char		*tampon;

	if (!line)
		return ;
	tampon = ft_strdup(line);
	node = p_try(sizeof(t_loc_var), CONTEXT);
	node->type = type;
	node->status = node->status | status;
	set_node_local(node, tampon);
	if (CTX(all_var))
		get_last_var()->next = node;
	else
		CTX(all_var) = node;
	ft_memdel((void **)&tampon);
}
