/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_reset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:03 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			cursor_reset(t_env *e)
{
	e->cursor->col = 0;
	e->cursor->row = 0;
	e->cursor->total = 0;
}
