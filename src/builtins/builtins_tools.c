/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 06:37:26 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/03 06:37:28 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void				builtin_setup_error(char *msg, t_env *e, int status)
{
	(msg) ? ft_putendl_fd(msg, 2) : 0;
	e->last_status = status;
}
