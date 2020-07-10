/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_parser_tf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:19 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		del_parser_tf(t_parser *tf)
{
	if (!tf)
		return ;
	if (tf->tok)
	{
		free(tf->tok);
		tf->tok = NULL;
	}
	if (tf->arg1)
	{
		free(tf->arg1);
		tf->arg1 = NULL;
	}
	if (tf->arg2)
	{
		free(tf->arg2);
		tf->arg2 = NULL;
	}
	tf->i = 0;
	tf->flag = 0;
	tf->ret = 0;
	free(tf);
	tf = NULL;
}
