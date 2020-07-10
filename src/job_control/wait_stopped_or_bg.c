/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_stopped_or_bg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 06:33:18 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/30 06:33:19 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		check_update_background(t_env *e, pid_t pid, int i)
{
	int			status;
	t_childs	*tmp;

	status = 0;
	if (waitpid(pid, &status, WUNTRACED | WNOHANG))
	{
		if (!(tmp = jobs_getter__bypid(pid, e)))
			return (-1);
		if (WIFEXITED(status))
		{
			if (i)
				ft_putchar_fd('\n', 2);
			jobs_print__event(tmp, E_DONE);
			return (1);
		}
		else if (WIFSIGNALED(status))
		{
			if (i)
				ft_putchar_fd('\n', 2);
			jobs_print__event(tmp, E_SIGTERMINATED);
			return (1);
		}
	}
	return (0);
}

static void		loop_destruct_bg_done(t_env *e)
{
	t_childs	*tmp;

	tmp = e->childs;
	while (tmp)
	{
		if (tmp->done == 'y')
		{
			jobs_destruct__bypid(tmp->child, e);
			tmp = e->childs;
			continue ;
		}
		tmp = tmp->next;
	}
}

int				stopped_or_bg(t_env *e)
{
	t_childs	*tmp;
	int			helper_cr;

	tmp = e->childs;
	helper_cr = 0;
	while (tmp)
	{
		if (tmp->foreground == 0 &&
			check_update_background(e, tmp->child, helper_cr))
		{
			tmp->done = 'y';
			helper_cr++;
		}
		tmp = tmp->next;
	}
	loop_destruct_bg_done(e);
	return (1);
}
