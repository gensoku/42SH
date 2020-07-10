/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check_arg_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:47:06 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		is_exept(char c)
{
	if (c == ';')
		return (1);
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (1);
	if (c == '\\')
		return (1);
	return (0);
}

static int		check_space_equal(char *str, int i)
{
	char		*cut;
	char		*tmp;

	if (!str)
		return (0);
	cut = ft_strchr(str, '=');
	if (cut)
	{
		cut[0] = 0;
		tmp = ft_strdup(str);
		cut[0] = '=';
	}
	else
		tmp = ft_strdup(str);
	i = -1;
	while (tmp[++i])
	{
		if (ft_isspace(tmp[i]) || is_symbol_(tmp[i]) || is_exept(tmp[i]))
		{
			ft_memdel((void **)&tmp);
			return (1);
		}
	}
	ft_memdel((void **)&tmp);
	return (0);
}

static	int		check_error_helper(char *str, int *opt)
{
	char		*cut;

	cut = ft_strchr(str, '=');
	if (cut)
	{
		cut[0] = 0;
		if (!is_var_(str))
			*opt = *opt | ER_EXP4;
		else
		{
			cut[0] = '=';
			return (0);
		}
		cut[0] = '=';
	}
	else
	{
		if (!is_var_(str))
			*opt = *opt | ER_EXP4;
		else
			return (0);
	}
	return (1);
}

int				check_error_exp(char *str, int *opt)
{
	if (*opt & FLAG_P_)
	{
		if (!check_error_helper(str, opt))
			return (0);
	}
	else
	{
		*opt = *opt | ER_SEND;
		if (check_space_equal(str, -1))
			*opt = *opt | ER_EXP5;
		else if (ft_isdigit(str[0]))
			*opt = *opt | ER_EXP6;
		else if (str[0] == '=' && !str[1])
			*opt = *opt | ER_EXP7;
		else if (str[0] == '=' && str[1])
			*opt = *opt | ER_EXP8;
		else
		{
			*opt = *opt - ER_SEND;
			return (0);
		}
	}
	CTX(last_status) = 1;
	return (1);
}

int				check_opt_exp(char *str, int *opt)
{
	int			i;

	if (!str)
		return (0);
	else if (str[0] == '-')
		i = 0;
	else
		i = -1;
	while (str[++i])
	{
		if (str[i] != 'p')
			return (0);
		else
			*opt = *opt | FLAG_P_;
	}
	return (1);
}
