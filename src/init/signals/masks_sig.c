/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   masks_sig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 08:31:51 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/08 08:32:14 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		signal_mask(int sig, int how)
{
	sigset_t mask;
	sigset_t omask;

	sigemptyset(&mask);
	sigaddset(&mask, sig);
	if (sigprocmask(how, &mask, &omask) != 0)
		ft_putendl_fd("signal masking failed", 2);
	return (sigismember(&omask, sig));
}

int				signal_block(int sig)
{
	return (signal_mask(sig, SIG_BLOCK));
}

int				signal_unblock(int sig)
{
	return (signal_mask(sig, SIG_UNBLOCK));
}
