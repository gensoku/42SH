/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_all_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 04:30:33 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:10 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			del_all_tokens(t_token *lst)
{
	t_token		*tmp;
	t_token		*tmp2;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		(tmp->tok) ? ft_memdel((void **)&tmp->tok) : (void)tmp->tok;
		(tmp->first) ? ft_memdel((void **)&tmp->first) : (void)tmp->first;
		(tmp->second) ? ft_memdel((void **)&tmp->second) : (void)tmp->second;
		ft_memdel((void **)&tmp);
		tmp = tmp2;
	}
}
