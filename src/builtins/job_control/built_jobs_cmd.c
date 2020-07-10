/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_fg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:43:27 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int				jobs_cmd__signal(t_childs *proc, t_env *e, t_jobscmd cmd)
{
	if (!proc || !proc->child)
		return (0);
	proc->running = 1;
	if (cmd == JOBS_FG)
	{
		tcsetattr(0, TCSANOW, &e->oterm);
		signal_block(SIGCHLD);
		tcsetpgrp(0, proc->grpid);
		proc->foreground = 1;
	}
	if (killpg(proc->grpid, SIGCONT) != 0)
		ft_putendl_fd("Error process", 2);
	jobs_setter__last(e->childs, proc->child);
	proc->stopped = 0;
	if (cmd == JOBS_FG)
	{
		wait_pgid(proc->grpid, e, 2);
		resume_state(e, 1, NULL);
		signal_unblock(SIGCHLD);
	}
	return (0);
}

int				jobs_cmd__number(char *arg, t_env *e, t_jobscmd cmd)
{
	t_childs		*proc;
	int				proc_n;
	int				size;

	size = get_size_childs(e->childs);
	proc_n = ft_atoi(arg);
	if (size < 1 || proc_n > size)
	{
		ft_putstr_fd("42sh: ", 2);
		jobs_cmd__print(cmd, 2);
		ft_putstr_fd(" ", 2);
		ft_putnbr_fd(proc_n, 2);
		ft_putendl_fd(": no such job", 2);
	}
	proc = e->childs;
	while (proc)
	{
		if (proc->id == proc_n)
			return (jobs_cmd__signal(proc, e, cmd));
		proc = proc->next;
	}
	return (0);
}

void			jobs_cmd__print(t_jobscmd cmd, int fd)
{
	if (cmd == JOBS_FG)
		ft_putstr_fd("fg", fd);
	else if (cmd == JOBS_BG)
		ft_putstr_fd("bg", fd);
	return ;
}

static int		jobs_cmd__router(char **array, t_env *e, t_jobscmd cmd)
{
	size_t		len;
	char		*arg;

	len = ft_len_tab(array);
	if (len < 1 || len > 2)
		return (0);
	if (len == 1)
		return (jobs_cmd__signal(jobs_getter__bylast(e->childs, 1), e, cmd));
	arg = array[1];
	if (ft_isnum_str(arg))
		return (jobs_cmd__number(arg, e, cmd));
	if (*arg == '+')
		return (jobs_cmd__signal(jobs_getter__bylast(e->childs, 1), e, cmd));
	if (ft_strcmp(arg, "-") == 0)
		return (jobs_cmd__signal(jobs_getter__bylast(e->childs, 0), e, cmd));
	jobs_cmd__print(cmd, 2);
	ft_putstr_fd(": usage: ", 2);
	jobs_cmd__print(cmd, 2);
	ft_putstr_fd(" [job_id|job_state]", 2);
	return (0);
}

void			jobs_cmd(char **array, t_env *e, t_jobscmd cmd)
{
	if (!jobs_cmd__router(array, e, cmd))
		return ;
}
