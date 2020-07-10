/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:47:13 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		ft_put_exp_error(char *str, int *opt)
{
	if (*opt & ER_EXP4)
	{
		*opt = *opt - ER_EXP4;
		ft_putstr_fd("export: no such variable: ", 2);
	}
	else if (*opt & ER_EXP5)
		ft_putstr_fd("export: not valid in this context: ", 2);
	else if (*opt & ER_EXP6)
		ft_putstr_fd("export: not an identifier: ", 2);
	else if (*opt & ER_EXP7)
	{
		ft_putstr_fd(SH_NAME, 2);
		builtin_setup_error(": bad assignement", CONTEXT, 1);
		return ;
	}
	else if (*opt & ER_EXP8)
	{
		ft_putstr_fd(SH_NAME, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		builtin_setup_error(" not found", CONTEXT, 1);
		return ;
	}
	builtin_setup_error(str, CONTEXT, 1);
}
