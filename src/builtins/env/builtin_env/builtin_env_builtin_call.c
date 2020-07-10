/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_builtin_call.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 09:11:29 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/03 09:11:30 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int			env_bui_call(t_env *e, char **array, unsigned long opts)
{
	int		i;

	i = 0;
	if (is_opt_set(opts, 'v') && verbose_lvl(2) > 1)
	{
		ft_putstr_fd("#env executing:  ", 2);
		ft_putendl_fd(array[i], 2);
		while (array[i])
		{
			ft_putstr_fd("#env    arg[", 2);
			ft_putnbr_fd(i, 2);
			ft_putstr_fd("]=  ", 2);
			ft_putendl_fd(array[i], 2);
			i++;
		}
	}
	if (get_builtin(&array[0], e, EXEC) != 1)
	{
		ft_putendl_fd("Internal error, builtin unable for any reason", 2);
		return (1);
	}
	return (0);
}
