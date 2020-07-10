/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 10:35:59 by tsedigi           #+#    #+#             */
/*   Updated: 2017/04/05 10:36:01 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

t_cursor		*cpy_cursor(t_cursor *cur)
{
	t_cursor	*dup;

	if (!(dup = (t_cursor *)ft_memalloc(sizeof(t_cursor))))
		return (dup);
	if (!cur)
		return (dup);
	dup->row = cur->row;
	dup->col = cur->col;
	dup->total = cur->total;
	return (dup);
}

t_quote			*cpy_quote(t_quote *cur)
{
	t_quote		*dup;

	if (!(dup = (t_quote *)ft_memalloc(sizeof(t_quote))))
		return (dup);
	if (!cur)
		return (dup);
	dup->pr = cur->pr;
	dup->bq = cur->bq;
	dup->ac = cur->ac;
	return (dup);
}
