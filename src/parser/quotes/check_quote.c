/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 09:38:31 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/16 09:02:23 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int					set_sep_flags(char *tmp, int i, int *flags, t_quote *count)
{
	int				ret;

	ret = 0;
	if ((ret = chk_less_dqu(tmp, i, flags, count)))
		*flags = *flags - FLAG_DQU;
	else if ((ret = chk_dqu(tmp, i, flags, count)))
		*flags = *flags | FLAG_DQU;
	else if ((ret = chk_less_qu(tmp, i, flags, count)))
		*flags = *flags - FLAG_QU;
	else if ((ret = chk_qu(tmp, i, flags, count)))
		*flags = *flags | FLAG_QU;
	else if ((ret = chk_xor_bqu(tmp, i, flags, count)))
		count->bq ^= 1;
	else if ((ret = chk_pr(tmp, i, flags, count)))
		count->pr++;
	else if ((ret = chk_less_pr(tmp, i, flags, count)))
		count->pr--;
	return (ret);
}

int					check_quote(t_env *e)
{
	int				i;
	char			*tmp;

	i = -1;
	tmp = e->line;
	if ((!tmp || !ft_strlen(tmp) || chk_tsp(tmp) == 0) && (E_F & FLAG_BACK))
		E_F = E_F - FLAG_BACK;
	else if (E_F & FLAG_BACK && CHECK_SL(tmp, ft_strlen(tmp) - 1) == 0)
		E_F -= FLAG_BACK;
	(chk_tsp(tmp) == 0) ? tmp = NULL : 0;
	if (tmp)
	{
		while (tmp[++i])
			set_sep_flags(tmp, i, &e->flag, e->count_qu);
		if (check_back_from(tmp, ft_strlen(tmp) - 1) % 2 != 0)
		{
			if (!(E_F & FLAG_QU) && !(E_F & FLAG_DQU) && !(E_F & FLAG_BACK) &&
				!e->count_qu->bq && !e->count_qu->pr)
				E_F = E_F | FLAG_BACK;
			if (!(E_F & FLAG_QU) && !(E_F & FLAG_DQU) &&
				!e->count_qu->bq && !e->count_qu->pr)
				tmp[ft_strlen(tmp) - 1] = 0;
		}
	}
	return (get_type_prompt(E_F, e->count_qu));
}
