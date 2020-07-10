/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:00:42 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		ft_set_term(struct termios *curent)
{
	if (tcsetattr(0, TCSANOW, curent) == -1)
		display_error(-1, "set term failed; exit", CONTEXT);
}

void		init_term_grp(pid_t pgid, pid_t pid, int foreground)
{
	(!pgid) ? pgid = getpid() : 0;
	(!pid) ? pid = getpid() : 0;
	setpgid(pid, pgid);
	(foreground) ? tcsetpgrp(0, pgid) : 0;
}
