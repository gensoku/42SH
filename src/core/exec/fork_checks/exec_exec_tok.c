/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exec_tok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/20 06:32:10 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int				exec_tok(char *save, t_env *e, int flag)
{
	char		**split;
	char		*trimed;
	int			ret;

	ret = 0;
	split = NULL;
	trimed = NULL;
	if (save)
	{
		if (chk_tsp(save) == 0)
			trimed = ft_strtrim(save);
		else
			trimed = ft_strdup(save);
		split = ft_strsplit_spec(trimed, 0);
		if (split)
		{
			if ((ret = get_builtin(split, e, EXEC)) != 1)
				adv_exec(e, split[0], split, flag);
			ft_del_tab(split);
			split = NULL;
		}
		if (trimed)
			ft_memdel((void**)&trimed);
	}
	return (ret);
}
