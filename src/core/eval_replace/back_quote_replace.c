/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_quote_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/20 06:33:19 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		setup_for_replace(int *k, char *line, t_quote *bqs, int *flags)
{
	while (line[*k] && bqs->bq)
	{
		(*k)++;
		set_sep_flags(line, *k, flags, bqs);
	}
}

static void		replace_back_quote(int k, int i, char **str)
{
	char		*line;
	t_quote		bqs;
	int			flags;

	line = *str;
	ft_bzero(&bqs, sizeof(t_quote));
	flags = 0;
	while (line && line[i])
	{
		if (!bqs.bq)
		{
			set_sep_flags(line, i, &flags, &bqs);
			if (bqs.bq)
			{
				k = i;
				setup_for_replace(&k, line, &bqs, &flags);
				if (line[k])
					bq_check_setup(&line, &i, &k, str);
			}
		}
		else
			set_sep_flags(line, i, &flags, &bqs);
		(line[i]) ? i++ : 0;
	}
}

void			check_replace_back_quote(char **line, t_env *e)
{
	if (!line && !*line)
		return ;
	replace_back_quote(0, 0, line);
	(void)e;
}
