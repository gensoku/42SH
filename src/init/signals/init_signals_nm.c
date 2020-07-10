/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals_nm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 08:45:36 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/08 08:45:38 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int			check_sig_out(int x)
{
	if (!x)
		return (0);
	if (x >= 1 && x <= 15)
		return (1);
	else if (x >= 24 && x <= 27)
		return (1);
	return (0);
}

static void			hlp_prc_st(void)
{
	if (CTX(proc_state))
	{
		tcsetattr(0, TCSANOW, &CTX(term));
		print_curseur(NULL);
		ft_putstr(CTX(line));
		cursor_set(CONTEXT, CTX(cursor), CTX(line));
	}
}

void				signal_child(int sig)
{
	int				status;
	pid_t			pid;
	t_childs		*tmp;

	(void)sig;
	if ((pid = waitpid(-1, &status, WUNTRACED | WNOHANG | WCONTINUED)) > 0)
	{
		if (WIFSIGNALED(status) && check_sig_out(WTERMSIG(status)))
		{
			tmp = jobs_getter__bypid(pid, CONTEXT);
			(!CTX(proc_state)) ? ft_putstr_fd("\n", 2) : 0;
			jobs_print__event(tmp, tmp->foreground ?
				E_SIGTERMINATED : E_SIGTERMINATED);
			jobs_destruct__bypid(pid, CONTEXT);
			(!CTX(proc_state)) ? CTX(proc_state) = 1 : 0;
			signal_child(0);
		}
	}
	else
	{
		hlp_prc_st();
		CTX(proc_state) = 0;
	}
}

void				reset_signals(void)
{
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
}

void				set_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGPIPE, SIG_DFL);
	signal(SIGWINCH, resize);
	signal(SIGCHLD, &signal_child);
}
