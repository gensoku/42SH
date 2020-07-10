/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_shell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/30 06:03:00 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int			set_shell_fg(void)
{
	int		shell_fd;
	pid_t	shell_pgid;

	shell_fd = STDIN_FILENO;
	if (!isatty(shell_fd))
		return (0);
	while (tcgetpgrp(shell_fd) != (shell_pgid = getpgrp()))
		kill(-shell_pgid, SIGTTIN);
	set_signals();
	shell_pgid = getpid();
	if (setpgid(shell_pgid, shell_pgid) < 0)
		display_error(-1, SH_INI, get_e(NULL));
	tcsetpgrp(shell_fd, shell_pgid);
	return (1);
}
