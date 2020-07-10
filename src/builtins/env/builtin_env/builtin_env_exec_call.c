/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_exec_call.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 06:16:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 07:29:42 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int			env_exec_call(t_env *e, char **array, unsigned long opts)
{
	int		i;

	i = 0;
	if (is_opt_set(opts, 'v') && !e->alt_path_line &&
		verbose_lvl(VERB_VAL) > 1)
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
	adv_exec(e, array[0], &array[0], 1);
	if (!e->pipe_builtin && e->tmp_pgid)
	{
		wait_pgid(e->tmp_pgid, e, 0);
		resume_state(e, 1, NULL);
	}
	return (0);
}
