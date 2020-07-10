/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exec_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 04:52:29 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/22 03:41:47 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		execve_2(t_env *e, char *name, char **tab1)
{
	if (e->envi != 0)
	{
		if ((execve(name, tab1, NULL)) == -1)
		{
			if (e->interactive)
				ft_putendl_fd("error execve call failed", 2);
			return (-1);
		}
	}
	else
	{
		if ((execve(name, tab1, (e->local_env) ?
			&e->local_env[0] : &e->env[0])) == -1)
		{
			if (e->interactive)
				ft_putendl_fd("error execve call failed", 2);
			return (-1);
		}
	}
	return (0);
}

int				execve_fork(t_env *e, char *name, char **tab1, char *full_name)
{
	if (name && full_name != NULL)
		return (execve_2(e, full_name, tab1));
	else
		return (execve_2(e, name, tab1));
	return (0);
}
