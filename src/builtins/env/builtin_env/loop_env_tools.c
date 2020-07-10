/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_env_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 08:40:19 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/03 08:40:20 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void				check_verbose_env_p(t_exe *matched, t_env *e, char **args)
{
	int				i;

	i = 0;
	if (verbose_lvl(VERB_VAL) > 1 && e->alt_path_line)
	{
		ft_putstr_fd("#env executing:  ", 2);
		ft_putendl_fd(matched->full_name, 2);
		while (args[i])
		{
			ft_putstr_fd("#env    arg[", 2);
			ft_putnbr_fd(i, 2);
			ft_putstr_fd("]=  ", 2);
			(i == 0) ? ft_putendl_fd(matched->full_name, 2) :
				ft_putendl_fd(args[i], 2);
			i++;
		}
	}
}

void				env_error(char *msg, int illegal, char opt)
{
	(msg) ? ft_putendl_fd(msg, 2) : 0;
	if (illegal)
	{
		ft_putstr_fd("illegal option : ", 2);
		ft_putchar_fd(opt, 2);
		ft_putchar_fd('\n', 2);
	}
	ft_putendl_fd("[-iv] [-P utilpath] [-S string] [-u name]", 2);
}

int					check_error_opts(char **tab1, int ret,
	unsigned long opts, t_env *e)
{
	int				i;

	i = 0;
	if (ret == -1)
	{
		env_error(NULL, 1, tab1[i][1]);
		reset_stuff(e, 1);
		return (1);
	}
	else if (((is_opt_set(opts, 'P') || is_opt_set(opts, 'S') ||
		is_opt_set(opts, 'u')) && !tab1[i + 1]))
	{
		env_error("option requires an argument", 0, 0);
		reset_stuff(e, 1);
		return (1);
	}
	return (0);
}
