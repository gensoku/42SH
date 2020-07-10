/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_exe_pipe_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 08:04:30 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/20 08:04:31 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		count_for_first_pipe(int opt)
{
	static int i = 0;

	if (opt && opt != 2)
		i++;
	else if (opt == 2)
		i = 0;
	return (i);
}

void			check_set_count_pipe(void)
{
	if (!count_for_first_pipe(0))
	{
		count_for_first_pipe(1);
		count_for_first_pipe(2);
	}
	else
		count_for_first_pipe(1);
}
