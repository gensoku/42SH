/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_is_builtin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:53:54 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int				check_exec_tok(char *save, t_env *e)
{
	char		**split;
	char		*trimed;

	split = NULL;
	if (save)
	{
		if (chk_tsp(save) == 0)
			trimed = ft_strtrim(save);
		else
			trimed = ft_strdup(save);
		split = ft_strsplit_spec(trimed, 0);
		if (split)
		{
			if (get_builtin(split, e, NO_EXEC) == 1)
			{
				ft_del_tab(split);
				(trimed) ? ft_memdel((void **)&trimed) : 0;
				return (1);
			}
			ft_del_tab(split);
		}
		if (trimed)
			ft_memdel((void**)&trimed);
	}
	return (0);
}
