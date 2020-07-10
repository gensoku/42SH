/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 05:49:58 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/22 08:11:56 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void		opts_u_helper(t_env *e, char *arg, unsigned long opts)
{
	char			*getter;
	char			**tmp;

	tmp = e->local_env;
	getter = get_env_line(e->local_env, arg);
	if (getter)
	{
		if (is_opt_set(opts, 'v') && verbose_lvl(VERB_VAL) > 1)
		{
			ft_putstr_fd("#env unset:     ", 2);
			ft_putendl_fd(arg, 2);
		}
		e->local_env = ft_del_from_tab(e->local_env, getter);
	}
	ft_del_tab(tmp);
	tmp = NULL;
	ft_memdel((void **)&getter);
}

int					env_opt_u(t_env *e, char *arg, unsigned long *opts)
{
	char			*getter;

	if (!e || !arg)
		return (ft_atoi("je sais pas coder si on entre ici"));
	if (e->local_env)
		opts_u_helper(e, arg, *opts);
	else
	{
		getter = get_env_line(e->env, arg);
		if (getter)
			e->local_env = ft_del_from_tab(e->env, getter);
	}
	ft_memdel((void **)&getter);
	check_opts("-u", "u", opts, 0 | SUPR_OPTS);
	return (1);
}
