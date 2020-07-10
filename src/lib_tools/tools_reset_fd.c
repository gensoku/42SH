/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_reset_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 09:49:17 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/08 09:49:18 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	reset_fd_(t_env *e)
{
	ft_memset((void *)&e->fd, -1, 12);
	ft_memset((void *)&e->ag_fd, -1, 12);
	dup2(e->std_fd[0], STDIN_FILENO);
	dup2(e->std_fd[1], STDOUT_FILENO);
	dup2(e->std_fd[2], STDERR_FILENO);
}
