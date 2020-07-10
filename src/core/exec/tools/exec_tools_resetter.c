/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools_resetter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/22 02:47:18 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void				resume_state(t_env *e, int opt, t_token *tmp)
{
	signal_unblock(SIGCHLD);
	tcsetattr(0, TCSADRAIN, &e->term);
	e->tmp_pgid = 0;
	reset_fd_(e);
	e->pipe_builtin = 0;
	if (opt)
	{
		if (e->foreground)
			tcsetpgrp(0, getpid());
		e->tmp_pgid = 0;
		e->foreground = 1;
		e->flag_pipe = 0;
		if (opt == 1)
			check_close_fd_redir(tmp, e);
		reset_fd_(e);
	}
	else
		tcsetpgrp(0, getpid());
}
