/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts_tools_debug.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 09:30:46 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/08 09:30:49 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void					debug_opts(unsigned long flags, char *opts)
{
	int					i;

	i = 0;
	if (!opts || !ft_strlen(opts))
		return ;
	if (!flags)
	{
		ft_putendl_fd("Aucune options activee, flag a 0 .", 2);
		return ;
	}
	while (opts[i])
	{
		ft_putstr_fd("le flag correspondant a [", 2);
		ft_putchar_fd(opts[i], 2);
		ft_putstr_fd("] est set a ", 2);
		ft_putendl_fd(is_opt_set(flags, opts[i]) ? "TRUE" : "FALSE", 2);
		i++;
	}
}
