/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 06:42:58 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/30 06:43:00 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		local_tools(t_env *e)
{
	if (e->flag_pipe)
	{
		close(e->flag_pipe);
		e->flag_pipe = 0;
	}
}

static void		setup_proc(t_childs *tmp, int opts, int code, int type)
{
	t_env		*e;

	e = get_e(NULL);
	local_tools(e);
	if (type == W_EXITED)
	{
		(!opts) ? e->last_status = code : 0;
		jobs_destruct__bypid(tmp->child, e);
	}
	else if (type == W_SIGNALED)
	{
		(!opts) ? e->last_status = code : 0;
		killpg(tmp->grpid, code);
		jobs_destruct__bypid(tmp->child, e);
	}
	else if (type == W_STOPPED)
	{
		(!opts) ? e->last_status = code : 0;
		tmp->stopped = 1;
		jobs_print__event(tmp, E_SIGSTOPPED);
		killpg(tmp->grpid, code);
	}
}

pid_t			wait_process(t_env *e, int opt)
{
	int			status;
	pid_t		pid;
	t_childs	*tmp;

	status = 0;
	pid = 0;
	if ((pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG)) > 0)
	{
		if (!(tmp = jobs_getter__bypid(pid, e)))
			return (pid);
		if (WIFEXITED(status))
			setup_proc(tmp, opt, WEXITSTATUS(status), W_EXITED);
		else if (WIFSIGNALED(status))
			setup_proc(tmp, opt, WTERMSIG(status), W_SIGNALED);
		else if (WIFCONTINUED(status))
		{
			tmp->stopped = 0;
			wait_pgid(tmp->grpid, e, opt);
		}
		else if (WIFSTOPPED(status))
			setup_proc(tmp, opt, WSTOPSIG(status), W_STOPPED);
	}
	return (pid);
}
