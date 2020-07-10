/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_reset_hash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 10:37:17 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:03:33 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"
#define LOC_MSG "\n Warning hash table reset, binary are maybe unavailable"

void	move_reset_hash(t_env *e)
{
	(e->paths) ? del_t_spath(e->paths) : 0;
	e->paths = NULL;
	(e->hash) ? ft_memdel((void **)&e->hash) : 0;
	set_exe(e);
	set_hash(e);
	ft_putstr_fd(LOC_MSG, 2);
	move_ctrl_c(e);
}
