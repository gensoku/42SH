/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 06:51:04 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/23 06:51:05 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int	check_recurs(unsigned long opts, char *to_check)
{
	if (!(*to_check))
		return (0);
	if (is_opt_set(opts, *to_check))
		return (1);
	return (check_recurs(opts, ++to_check));
}

int			check_opt_conflict(unsigned long opts, char *to_check)
{
	int		i;

	if (!to_check || !opts)
		return (0);
	i = -1;
	while (to_check[++i])
		if (is_opt_set(opts, to_check[i]) &&
			check_recurs(opts, &to_check[i + 1]))
			return (1);
	return (0);
}

char		get_opt_arg(unsigned long opts, char *args, int flag)
{
	int		valid;
	char	ret;

	valid = 0;
	ret = 0;
	while (args && *args)
	{
		if ((valid = is_opt_set(opts, *args)) && valid != -1)
		{
			if (flag & FIRST_ARG)
				return (*args);
			else
				ret = *args;
		}
		args++;
	}
	return (ret);
}
