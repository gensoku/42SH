/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_args_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 07:41:50 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:05:02 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	char			*ft_free_add(char *tmp, char c)
{
	char		*ret;

	if (!c)
		return (tmp);
	ret = ft_strnew(ft_strlen(tmp) + 2);
	if (tmp)
		ft_strcat(ret, tmp);
	ret[ft_strlen(ret)] = c;
	if (tmp)
		free(tmp);
	tmp = NULL;
	return (ret);
}

static	void			pars_4(t_parser *tf, char *line)
{
	if (ft_isspace(line[tf->i]) == 1)
	{
		if (tf->arg1)
		{
			tf->arg1 = ft_free_add(tf->arg1, line[tf->i]);
			tf->flag = 0;
		}
	}
	else
	{
		tf->arg1 = ft_free_add(tf->arg1, line[tf->i]);
		tf->flag = 0;
	}
}

void					loop_args_token(t_parser *tf, char *line)
{
	if (tf->tok)
	{
		if (ft_isspace(line[tf->i]) == 1)
		{
			if (tf->arg2)
			{
				tf->arg2 = ft_free_add(tf->arg2, line[tf->i]);
				tf->flag = 0;
			}
		}
		else
		{
			tf->arg2 = ft_free_add(tf->arg2, line[tf->i]);
			tf->flag = 0;
		}
	}
	else
		pars_4(tf, line);
	tf->i++;
}
