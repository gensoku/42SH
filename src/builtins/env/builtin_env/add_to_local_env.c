/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_local_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 05:47:59 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 07:14:56 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void	add_local(t_env *e, char **args)
{
	char				*cut;
	char				*getter;
	char				**tmp_ar;

	getter = NULL;
	if ((cut = ft_strchr(*args, '=')))
	{
		cut[0] = 0;
		getter = get_env_line(e->local_env, *args);
		cut[0] = '=';
		if (getter)
		{
			tmp_ar = e->local_env;
			e->local_env = ft_del_from_tab(e->local_env, getter);
			ft_del_tab(tmp_ar);
		}
	}
	tmp_ar = e->local_env;
	e->local_env = ft_add_to_tab(e->local_env, *args, NULL);
	ft_del_tab(tmp_ar);
	tmp_ar = NULL;
	ft_memdel((void **)&getter);
}

static	void	add_local_from_env(t_env *e, char **args)
{
	char				*cut;
	char				*getter;
	char				**tmp_ar;

	getter = NULL;
	if ((cut = ft_strchr(*args, '=')))
	{
		cut[0] = 0;
		getter = get_env_line(e->env, *args);
		cut[0] = '=';
		if (getter)
			e->local_env = ft_del_from_tab(e->env, getter);
	}
	tmp_ar = e->local_env;
	e->local_env = ft_add_to_tab(e->local_env ?
		e->local_env : e->env, *args, NULL);
	(tmp_ar) ? ft_del_tab(tmp_ar) : 0;
	tmp_ar = NULL;
	ft_memdel((void **)&getter);
}

void			add_to_local_env(t_env *e, char **args, unsigned long opts)
{
	if (!args || !*args)
		return ;
	if (e->local_env)
		add_local(e, args);
	else
		add_local_from_env(e, args);
	if (is_opt_set(opts, 'v'))
	{
		ft_putstr_fd("setenv : ", 2);
		ft_putendl_fd(*args, 2);
	}
}
