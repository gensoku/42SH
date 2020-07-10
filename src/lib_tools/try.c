/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 06:27:34 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/03 06:27:36 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		*p_try(size_t size, t_env *e)
{
	void	*p;

	if ((p = ft_memalloc(size)) == NULL)
		display_error(-1, "Malloc failed safety exit", e);
	return (p);
}
