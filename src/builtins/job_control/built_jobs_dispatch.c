/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_jobs_dispatch.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 05:37:48 by tsedigi           #+#    #+#             */
/*   Updated: 2017/04/22 05:37:49 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void				built_fg(char **array, t_env *e)
{
	jobs_cmd(array, e, JOBS_FG);
}

void				built_bg(char **array, t_env *e)
{
	jobs_cmd(array, e, JOBS_BG);
}
