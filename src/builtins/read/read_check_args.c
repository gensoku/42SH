/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_check_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 07:30:02 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/23 07:30:04 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int	is_format_opt(unsigned long opts, char *format)
{
	while (format && *format)
	{
		if (is_opt_set(opts, *format))
			return (1);
		format++;
	}
	return (0);
}

static void	set_struc_args(char arg, t_read *r)
{
	int		integer;

	integer = 0;
	if (arg == 't' || arg == 'u' || arg == 'n')
	{
		integer = ft_atoi(*(r->args));
		(integer < 0) ? integer *= -1 : 0;
		(arg == 't') ? r->timeout = integer : 0;
		(arg == 'u') ? r->fd = integer : 0;
		(arg == 'n') ? r->nchars = integer : 0;
	}
	else if (arg == 'a')
		r->a_arr = ft_strdup(*(r->args));
	else if (arg == 'p')
		r->prompt = ft_strdup(*(r->args));
	else if (arg == 'd')
		r->delim = (*(r->args))[0];
}

int			set_read_args(t_read *r, unsigned long opts)
{
	if (check_opt_conflict(opts, BUI_READ_CONF))
		return (p_read_err(*(r->args), 3, 0));
	else if (opt_with_arg(opts, BUI_READ_CONF))
	{
		if (is_opt_set(r->opts, get_opt_arg(opts, BUI_READ_CONF, FIRST_ARG)))
		{
			return (p_read_err(NULL, 7,
				get_opt_arg(opts, BUI_READ_CONF, FIRST_ARG)));
		}
		check_opts(*(r->args), BUI_READ_OPTS, &r->opts, SET_OPTS);
		r->args++;
		if (opts_w_arg_chk(opts, r->args ? *(r->args) : NULL))
			return (-1);
		set_struc_args(get_opt_arg(opts, BUI_READ_CONF, FIRST_ARG), r);
	}
	else
		check_opts(*(r->args), BUI_READ_OPTS, &r->opts, SET_OPTS);
	return (0);
}

int			opts_w_arg_chk(unsigned long opts, char *line)
{
	if (opt_with_arg(opts, BUI_READ_CONF))
	{
		if (!line)
		{
			return (p_read_err(NULL, 2,
				get_opt_arg(opts, BUI_READ_CONF, FIRST_ARG)));
		}
		else if (!ft_strlen(line))
			return (p_read_err(line, 4, 0));
		if (is_format_opt(opts, R_DIGIT_OPT) &&
			wrong_read_name(line, DIGIT_FORMAT))
			return (p_read_err(line, 6, 0));
		else if (is_format_opt(opts, R_ALPHA_OPT) &&
			wrong_read_name(line, ASC_FORMAT))
			return (p_read_err(line, 5, 0));
	}
	return (0);
}

int			pre_check_args(char **array, int i)
{
	if (!array || !array[i])
		return (0);
	if (!ft_strlen(array[i]) || wrong_read_name(array[i], ALNUM_FORMAT))
		return (p_read_err(array[i], 4, 0));
	return (pre_check_args(&array[0], ++i));
}
