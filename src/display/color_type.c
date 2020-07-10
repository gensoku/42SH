/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 11:26:03 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/03 11:26:04 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void		set_color_type(int type)
{
	if (type == F_DIR)
		ft_putstr(RED);
	else if (type == F_SYMLINK)
		ft_putstr(BLUE);
	else if (type == F_BLK)
		ft_putstr(GREEN);
	else if (type == F_CHR)
		ft_putstr(YELLOW);
	else if (type == F_FIFO)
		ft_putstr(CYAN);
	else if (type == F_SOCK)
		ft_putstr(MAGENT);
	else if (type == F_REG)
		ft_putstr(WHITE);
}
