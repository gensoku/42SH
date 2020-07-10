/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_adv_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 04:26:41 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 07:49:35 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void	print_bg_pid_content(void)
{
	ft_putstr_fd("[", WCH_FD);
	ft_putnbr_fd((jobs_getter__bypgid(getpgid(getpid()), CONTEXT)) ?
		jobs_getter__bypgid(getpgid(getpid()), CONTEXT)->id :
			push_front_child_id(CTX(childs), CTX(childs), 1), WCH_FD);
	ft_putstr_fd("] ", WCH_FD);
}

static	void	print_bg_pid(int trigger)
{
	int			z;
	t_childs	*tmp;

	z = 0;
	if (!trigger)
		return ;
	tmp = CTX(childs);
	if (!tmp)
		ft_putstr_fd("[1] ", WCH_FD);
	while (tmp)
	{
		if (z == 0)
			print_bg_pid_content();
		if (tmp->grpid == getpgid(getpid()))
		{
			ft_putnbr_fd(tmp->child, WCH_FD);
			ft_putstr_fd(" ", WCH_FD);
		}
		tmp = tmp->next;
		z++;
	}
	ft_putnbr_fd(getpid(), WCH_FD);
	ft_putchar_fd('\n', WCH_FD);
}

static	void	load_exec(t_env *e, char *name, char **tab1, char *full_name)
{
	pid_t	son;
	int		ret;

	signal_block(SIGCHLD);
	(e->foreground) ? tcsetattr(0, TCSANOW, &e->oterm) : 0;
	((son = fork()) == -1) ? display_error(-1, "Fork failed, exit", e) : 0;
	if (son == 0)
	{
		reset_signals();
		signal_unblock(SIGCHLD);
		init_term_grp((e->tmp_pgid) ? e->tmp_pgid :
			getpid(), getpid(), e->foreground);
		adv_exec_set_fds(e);
		print_bg_pid(e->display_bg);
		ret = execve_fork(e, name, tab1, full_name);
		signal_block(SIGCHLD);
		ft_putstr_fd((full_name && e->interactive) ? full_name : name, 2);
		ft_putendl_fd(" Command not found ", 2);
		ft_exit(ret, e, 1);
	}
	(!e->tmp_pgid) ? e->tmp_pgid = son : 0;
	init_term_grp((e->tmp_pgid) ? e->tmp_pgid : son, son, e->foreground);
	push_front_child(son, e, name, e->foreground);
	e->childs->grpid = getpgid(son);
	e->foreground = 1;
}

int				adv_exec(t_env *e, char *name, char **tab1, int flag)
{
	t_exe		*tmp;

	tmp = NULL;
	if (!adv_check_valid(&tmp, name, tab1, e))
		return (0);
	if (tmp && tmp->full_name && flag == 1)
		load_exec(e, name, tab1, tmp->full_name);
	else if (flag == 1)
		load_exec(e, name, tab1, NULL);
	else if (flag == 0 && tmp && tmp->full_name)
		execve_fork(e, name, tab1, tmp->full_name);
	else if (flag == 0)
		execve_fork(e, name, tab1, NULL);
	tmp = NULL;
	return (adv_exec_invalid(e, 0));
}
