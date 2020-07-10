/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/16 11:59:01 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		rplc_f(char **line2, char **line, char **tmp, char **replace)
{
	if (tmp && *tmp)
	{
		(void)line;
		ft_memdel((void **)line2);
		*line2 = ft_strdup(*tmp);
		ft_memdel((void **)tmp);
		ft_memdel((void **)replace);
		return (1);
	}
	ft_memdel((void **)replace);
	return (0);
}

static int		setup_replace(char **line, char **line2, int *i, int k)
{
	char		*replace;
	t_env		*e;
	t_loc_var	*loc_var;
	char		*tmp;

	e = CONTEXT;
	replace = NULL;
	tmp = NULL;
	while (line2 && (*line2)[++k])
	{
		if (check_dollar_end(*line2, k) || !(*line2)[k + 1])
		{
			replace = ft_strsub(*line2, (*i) + 1,
				check_dollar_end(*line2, k) ? k - (*i) - 1 : k - *i);
			if ((loc_var = get_var_ptr(e, replace, CASE_FALSE)) &&
				(loc_var->type || !ft_strcmp(replace, "?")))
				tmp = ft_str_sub_append(*line2, loc_var->value, *i,
					check_dollar_end(*line2, k) ? k - *i : k - (*i) + 1);
			return (rplc_f(line2, line, &tmp, &replace));
		}
	}
	return (0);
}

static int		check_error_loc_var(char **line, t_env *e)
{
	if (!line || !*line)
		return (0);
	if (e->flag & FLAG_QU && !ft_strchr(*line, '\''))
		return (0);
	return (1);
}

static void		init_togs(int *toggle, int *toggle2, int *toggle_bq, int *ret)
{
	*toggle = CTX(flag) & FLAG_DQU ? 1 : 0;
	*toggle2 = CTX(flag) & FLAG_QU ? 1 : 0;
	*toggle_bq = CTX(count_qu)->bq;
	*ret = 0;
}

int				loc_var_rep(t_env *e, char **line, int i, int k)
{
	int			arr[4];
	char		*line2;

	if (!check_error_loc_var(line, e))
		return (0);
	init_togs(&arr[0], &arr[1], &arr[2], &arr[3]);
	line2 = *line;
	while (line2[i])
	{
		if (!arr[1] && !arr[2] && line2[i] == '\"')
			arr[0] ^= 1;
		else if (!arr[0] && !arr[2] && line2[i] == '\'')
			arr[1] ^= 1;
		else if (line2[i] == '`')
			arr[2] ^= 1;
		else if (!arr[1] && line2[i] == '$' &&
			!(check_back_from(line2, i - 1) % 2))
		{
			k = i;
			arr[3] += setup_replace(line, &line2, &i, k);
		}
		i++;
	}
	*line != line2 ? *line = line2 : 0;
	return (arr[3]);
}
