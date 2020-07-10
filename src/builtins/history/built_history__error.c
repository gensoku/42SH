/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history__error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:48:00 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/12 10:48:03 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		built_history__error_print(char *msg)
{
	ft_putstr_fd("history: ", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

int				built_history__error(t_herror error)
{
	if (error == HISTORY_NOT_FOUND)
		return (built_history__error_print("event not found"));
	if (error == HISTORY_TOO_MANY_ARG)
		return (built_history__error_print("too many arguments"));
	if (error == HISTORY_EMPTY_ARG)
		return (built_history__error_print("empty arg provided"));
	if (error == HISTORY_OPT_ILLEGAL)
		return (built_history__error_print("illegal option"));
	return (0);
}
