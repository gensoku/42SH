/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/16 11:53:24 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		init_togs(int *toggle, int *toggle2, int *ret, int *k)
{
	*toggle = CTX(flag) & FLAG_DQU ? 1 : 0;
	*toggle2 = CTX(flag) & FLAG_QU ? 1 : 0;
	*ret = 0;
	*k = 0;
}

static int		check_error_rep_hist(char **line, t_env *e)
{
	if (!line || !*line)
		return (0);
	if (e->flag & FLAG_QU && !ft_strchr(*line, '\''))
		return (0);
	return (1);
}

static void		set_check_toogle(int *var1, int *var2, char c, int opts)
{
	if (opts)
	{
		if (!var1 && c == '\"')
			*var2 ^= 1;
	}
	else
	{
		if (!var2 && c == '\'')
			*var1 ^= 1;
	}
}

static int		get_end_replace(char *line, int i)
{
	i++;
	while (ft_isdigit(line[i]))
		i++;
	if (ft_isdigit(line[i - 1]))
		i--;
	return (i);
}

int				check_history_replace(t_env *e, int i)
{
	char		*line;
	int			arr[5];

	line = e->line;
	if (!check_error_rep_hist(&line, e))
		return (0);
	init_togs(&arr[0], &arr[1], &arr[2], &arr[4]);
	while (e->line && e->line[i])
	{
		set_check_toogle(&arr[1], &arr[0], e->line[i], 1);
		set_check_toogle(&arr[0], &arr[1], e->line[i], 0);
		if (!arr[0] && (!arr[1] || ft_strchr(&e->line[i + 1], '\"')) &&
			e->line[i] == '!' && !(check_back_from(e->line, i - 1) % 2) &&
			(e->line[i + 1] && ft_isdigit(e->line[i + 1])))
		{
			arr[3] = i;
			i = get_end_replace(e->line, i);
			arr[2] += hist_setup_replace(i, arr[3], &e->line);
		}
		i++;
	}
	return (arr[2]);
}
