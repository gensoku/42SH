/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 06:11:55 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/23 06:11:56 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int					wrong_read_name(char *line, int opts)
{
	if (!line || !ft_strlen(line))
		return (1);
	while (*line)
	{
		if (opts == ASC_FORMAT && !ft_isalpha(*line))
			return (1);
		else if (opts == DIGIT_FORMAT && !ft_isdigit(*line))
			return (1);
		else if (opts == ALNUM_FORMAT && !ft_isalnum(*line))
			return (1);
		line++;
	}
	return (0);
}

int					opt_with_arg(unsigned long opts, char *all_opts_arg)
{
	while (all_opts_arg && *all_opts_arg)
	{
		if (is_opt_set(opts, *all_opts_arg))
			return (1);
		all_opts_arg++;
	}
	return (0);
}

int					p_read_err(char *line, int type_err, char c)
{
	(line && type_err < 4) ? ft_putstr_fd(line, 2) : 0;
	(!line && type_err < 4) ? ft_putchar_fd(c, 2) : 0;
	(!type_err) ? ft_putstr_fd(": Error", 2) : 0;
	(type_err == 1) ? ft_putendl_fd(": invalid option", 2) : 0;
	(type_err == 2) ? ft_putendl_fd(": argument required", 2) : 0;
	(type_err == 3) ? ft_putstr_fd(": options wich require args ", 2) : 0;
	(type_err == 3) ? ft_putendl_fd("should be separated by the arg", 2) : 0;
	if (type_err < 4)
	{
		ft_putstr_fd("read: usage: read [-ers] [-u fd] [-t timeout] [-p", 2);
		ft_putstr_fd(" prompt] [-a array] [-n nchars]", 2);
		ft_putendl_fd(" [-d delim] [name ...]", 2);
	}
	else
	{
		(type_err == 4) ? ft_putstr_fd("Not an identifier: ", 2) : 0;
		(type_err == 5) ? ft_putstr_fd("arg required is alpha: ", 2) : 0;
		(type_err == 6) ?
			ft_putstr_fd("arg required is postitiv digit: ", 2) : 0;
		(type_err == 7) ? ft_putstr_fd("option as already been set : ", 2) : 0;
		line ? ft_putstr_fd(line, 2) : ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
	}
	CTX(last_status) = 1;
	return (-1);
}

static int			set_check_args(t_read *r)
{
	int				ret;
	unsigned long	opts;

	ret = 0;
	opts = 0;
	while (r->args && (ret = check_opts(*(r->args), BUI_READ_OPTS,
		&opts, SET_OPTS)) && ret != -1)
	{
		if ((set_read_args(r, opts)))
			return (-1);
		opts = 0;
		r->args ? r->args++ : 0;
	}
	if (ret == -1)
		return (p_read_err(*(r->args), 1, 0));
	if (pre_check_args(r->args, 0))
		return (-1);
	return (0);
}

void				ft_read(char **array, t_env *e)
{
	t_read			r;

	ft_bzero((void *)&r, sizeof(t_read));
	if (!array)
	{
		e->last_status = 1;
		return ;
	}
	if (!array[1])
		read__read_display(CONTEXT, &r);
	else
	{
		r.args = &array[1];
		if (set_check_args(&r) == -1)
		{
			ft_memdel((void **)&r.prompt);
			ft_memdel((void **)&r.a_arr);
			ft_bzero((void *)&r, sizeof(t_read));
			return ;
		}
		read__read_display(CONTEXT, &r);
	}
	ft_memdel((void **)&r.prompt);
	ft_memdel((void **)&r.a_arr);
	ft_bzero((void *)&r, sizeof(t_read));
}
