/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_set.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 00:17:52 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 08:57:51 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			cursor_set(t_env *e, t_cursor *cur, char *line)
{
	int	col_1;
	int	max;

	cur->row = 0;
	cur->col = 0;
	cur->total = ft_strlen(line);
	max = cur->total;
	col_1 = e->col - get_size_prompt(NULL);
	if (max - col_1 >= 0)
	{
		cur->row++;
		max -= col_1;
		while (max - e->col >= 0)
		{
			cur->row++;
			max -= e->col;
		}
		if (max >= 0)
			cur->col = max;
	}
	else
		cur->col = max;
}
