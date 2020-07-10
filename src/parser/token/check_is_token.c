/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 09:54:47 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:05:00 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int		ret_sub_parse(t_parser *tf, int ret)
{
	tf->type = SUB_RED;
	tf->agreg_int = 1;
	return (ret);
}

static	int		parser_sub(char *line, int i, t_parser *tf, t_env *e)
{
	int			ret;
	t_quote		ct;
	int			flag;
	int			k;

	ret = 1;
	flag = 0;
	k = tf->i;
	ft_bzero(&ct, sizeof(t_quote));
	if (!e->flag && !e->count_qu->bq && e->count_qu->pr == 1 &&
		line[k] == '(' && (check_back_from(line, i - 1) % 2 == 0) &&
		set_sep_flags(line, k, &flag, &ct))
	{
		k++;
		while (line[k])
		{
			set_sep_flags(line, k, &flag, &ct);
			ret++;
			k++;
			if (!flag && !ct.pr && !ct.bq)
				return (ret_sub_parse(tf, ret));
		}
	}
	return (0);
}

static	int		p_or_and_redir(char *line, int i, t_parser *tf)
{
	if (line[i] == '|' && line[i + 1] && line[i + 1] == '|')
	{
		tf->type = OR_RE;
		return (2);
	}
	else if (line[i] == '|')
	{
		tf->type = P_REDIR;
		return (1);
	}
	if (line[i] == '&' && line[i + 1] && line[i + 1] == '&')
	{
		tf->type = AND_RE;
		return (2);
	}
	else if (line[i] == '&')
	{
		tf->agreg_int = 1;
		tf->type = BACK_PROCESS_REDIR;
		return (1);
	}
	return (0);
}

int				ft_istoken(char *line, int i, t_parser *tf, t_env *e)
{
	int		ret;

	ret = 0;
	if (!line)
		return (0);
	if (e->flag & FLAG_DQU || e->flag & FLAG_QU)
		return (0);
	if (tf->back_flag > 0)
		return (0);
	if (e->count_qu->bq > 0)
		return (0);
	if (e->save_type == 0 && tf->type != 0)
		e->save_type = tf->type;
	if ((ret = parser_sub(line, tf->i, tf, e)))
		return (ret);
	if ((ret = parser_left_(line, tf->i, tf)) != 0)
		return (ret);
	else if ((ret = parser_right_(line, tf->i, tf)) != 0)
		return (ret);
	else if ((ret = parser_r_agreg_(line, tf->i, tf)) != 0)
		return (ret);
	else if ((ret = parser_l_agreg_(line, tf->i, tf)) != 0)
		return (ret);
	return (p_or_and_redir(line, i, tf));
}
