/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_histo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:02:04 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		save_histo_(t_env *e, char *tmp)
{
	if (tmp)
		e->histo = push_front_histo(e, tmp);
	else
		e->histo = push_front_histo(e, e->saved_histo);
}
