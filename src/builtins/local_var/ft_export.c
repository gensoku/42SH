/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:47:34 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void					export_to_setenv(char *line, char **setter, char *cut)
{
	setter = p_try(sizeof(char *) * 4, CONTEXT);
	cut = ft_strchr(line, '=');
	setter[0] = "ft_setenv";
	if (cut)
	{
		cut[0] = 0;
		setter[1] = ft_strdup(line);
		if (cut[1])
			setter[2] = ft_strdup(&cut[1]);
		else
			setter[2] = ft_strdup("\'\'");
		cut[0] = '=';
	}
	else
	{
		setter[1] = ft_strdup(line);
		setter[2] = ft_strdup("\'\'");
	}
	setter[3] = NULL;
	ft_setenv(setter, CONTEXT);
	(setter[1]) ? ft_memdel((void **)&setter[1]) : 0;
	(setter[2]) ? ft_memdel((void **)&setter[2]) : 0;
	free(setter);
}

static	void			ft_export_loop(char **arg, int i, int *opt)
{
	while (arg[i])
	{
		if (!(*opt & ER_SEND) && check_error_exp(arg[i], opt))
			ft_put_exp_error(arg[i], opt);
		else if (!check_error_exp(arg[i], opt))
			(*opt & FLAG_P_) ? display_var_p(arg[i], 0)
			: check_for_set(arg[i]);
		i++;
	}
}

void					ft_export(char **arg, t_env *e)
{
	int					opt;
	int					i;

	opt = 0;
	(void)e;
	if (!arg)
		return ;
	i = 1;
	if (arg[1] && arg[1][0] == '-')
	{
		if (!check_opt_exp(&arg[1][1], &opt))
		{
			builtin_setup_error(EXP_ER_OPT, e, 1);
			return ;
		}
		i++;
	}
	if (!arg[i])
		(opt & FLAG_P_) ? display_var_p(NULL, 1) : display_var_no_p();
	else
		ft_export_loop(arg, i, &opt);
}
