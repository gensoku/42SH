/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_loop_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 09:05:43 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void			loop_treat(t_env *e, char buf[MAX_LEN + 4],
	int i, uint64_t *y)
{
	unsigned char	*s;

	i = 0;
	*y = 0;
	if (buf[0] != 27 && buf[0] != 4)
	{
		while (buf[i])
		{
			moves_display((int)buf[i], e);
			i++;
		}
	}
	else
	{
		i = 0;
		s = (unsigned char*)buf;
		while (i < 8)
		{
			*y += (s[i] << (8 * i));
			i++;
		}
		moves_display(*y, e);
	}
}

void				read_display(t_env *e, int x)
{
	char			buf[MAX_LEN + 1 + 3];
	int				z;
	uint64_t		y;

	ft_bzero(buf, MAX_LEN + 1);
	(void)x;
	z = 0;
	y = 0;
	while (y != 4 || (y == 4 && z != 0))
	{
		ft_bzero(buf, MAX_LEN + 1);
		read(0, buf, MAX_LEN);
		if (buf[0])
			loop_treat(e, buf, 0, &y);
		z = (e->line && ft_strlen(e->line) > 0) ? 1 : 0;
	}
	ft_putchar('\n');
	ft_exit(0, e, 0);
}
