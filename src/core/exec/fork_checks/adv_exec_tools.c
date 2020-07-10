/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_exec_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 06:12:43 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/20 06:12:44 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void	adv_norm_put(char *name, int opt, t_env *e)
{
	if (!opt)
	{
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": Error permission denied", 2);
		e->last_status = 1;
	}
	else if (!get_var_ptr(e, "intern_sys_call", CASE_TRUE))
	{
		ft_putstr_fd(name, 2);
		ft_putendl_fd(ERR_CMD, 2);
		e->last_status = 1;
	}
}

int				adv_check_valid(t_exe **tmp, char *name, char **tab1, t_env *e)
{
	if (name && (*tmp = (get_exe_hash(name, e))) != NULL)
	{
		check_verbose_env_p(*tmp, e, tab1);
		if (access((*tmp)->full_name, X_OK) != 0)
		{
			adv_norm_put(name, 0, e);
			return (adv_exec_invalid(e, 1));
		}
	}
	else if (access(name, X_OK) == 0)
	{
		if (check_stats_type(name, e) == -1)
			return (adv_exec_invalid(e, 1));
	}
	else
	{
		adv_norm_put(name, 2, e);
		return (adv_exec_invalid(e, 1));
	}
	return (1);
}

int				adv_exec_invalid(t_env *e, int update_stat)
{
	e->local_env ? ft_del_tab(e->local_env) : 0;
	e->local_env = NULL;
	update_stat ? e->last_status = 1 : 0;
	return (0);
}

void			adv_exec_set_fds(t_env *e)
{
	(e->flag_pipe) ? dup2(e->flag_pipe, STDIN_FILENO) : 0;
	(e->fd[0] != -1) ? dup2(e->fd[0], STDOUT_FILENO) : 0;
	(e->fd[1] != -1) ? dup2(e->fd[1], STDERR_FILENO) : 0;
	(e->fd[2] != -1) ? dup2(e->fd[2], STDIN_FILENO) : 0;
}

int				check_stats_type(char *name, t_env *e)
{
	struct stat	sts;
	const int	ret_error[8] = {
		0, 6, 2, 3, 4, 5, 0, 7};
	int			type;

	if (stat(name, &sts) != -1)
	{
		type = typedefineargs(sts.st_mode);
		return (ret_error[type] ?
			(e->last_status = set_ret_error(ret_error[type], name)) : 0);
	}
	return (0);
}
