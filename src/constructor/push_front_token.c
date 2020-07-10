/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_front_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:48:13 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			push_front_token(char *tok, t_parser *tf, t_env *e)
{
	t_token		*node;

	if ((node = (t_token*)ft_memalloc(sizeof(t_token))) == NULL)
		display_error(-1, "malloc failed t_token", e);
	node->tok = ft_strdup(tok);
	node->first = tf->arg1 ? ft_strdup(tf->arg1) : NULL;
	node->second = tf->arg2 ? ft_strdup(tf->arg2) : NULL;
	node->foreground = 1;
	if (e->save_type != 0)
		node->type = e->save_type;
	else
		node->type = tf->type;
	e->save_type = tf->type;
	tf->type = 0;
	if (e->split_tok)
	{
		node->next = e->split_tok;
		e->split_tok->previous = node;
	}
	else
		node->next = NULL;
	e->split_tok = node;
}
