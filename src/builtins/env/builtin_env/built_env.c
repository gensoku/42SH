/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 07:58:44 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 09:58:46 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int						reset_stuff(t_env *e, int status)
{
	e->envi = 0;
	ft_del_tab(e->local_env);
	del_t_spath(e->alternate_paths);
	e->alternate_paths = NULL;
	ft_memdel((void **)&e->alt_path_line);
	verbose_lvl(RESET_VERBOSE);
	e->local_env = NULL;
	if (status != POISON)
		e->last_status = status;
	return (1);
}

static	int				option_next_av(char **tab1, int i,
	unsigned long *opts, t_env *e)
{
	if (is_opt_set(*opts, 'P'))
	{
		if (env_opt_p(e, tab1[i], opts))
			return (2);
		check_opts("-P", "P", opts, 0 | SUPR_OPTS);
		return (1);
	}
	if (is_opt_set(*opts, 'S'))
	{
		e->last_status = (env_opt_s(e, tab1[i], opts)) ? 1 : 0;
		if (e->last_status)
		{
			reset_stuff(e, e->last_status == 1 ? 0 : 1);
			return (2);
		}
		return (1);
	}
	if (is_opt_set(*opts, 'u'))
	{
		env_opt_u(e, tab1[i], opts);
		return (1);
	}
	return (0);
}

static	int				mini_setter(char *arg, unsigned long *opts, t_env *e)
{
	int					ret;

	ret = (arg) ? check_opts(arg, "iPSuv", opts, SET_OPTS) : 1;
	is_opt_set(*opts, 'i') ? e->envi = 1 : 0;
	return (ret);
}

static	int				m_l(int ret, int *i, char **tab1, unsigned long *opts)
{
	if ((ret = option_next_av(tab1, *i, opts, CONTEXT)) == 2)
		return (1);
	else if (ret)
		*(i) += 1;
	ret = mini_setter(tab1[*i], opts, CONTEXT);
	if (ret && ret != -1 && ft_strchr(tab1[*i], 'v'))
		display_verbose_lvl(how_many_char(tab1[*i], 'v'));
	if (check_error_opts(&tab1[*i], ret, *opts, CONTEXT))
		return (1);
	else if (!tab1[*i])
		return (2);
	else if (ret)
		return (0);
	else if (get_builtin(&tab1[*i], CONTEXT, NO_EXEC) == 1)
		return (reset_stuff(CONTEXT, env_bui_call(CONTEXT, &tab1[*i], *opts)));
	else if (ft_strchr(tab1[*i], '='))
		add_to_local_env(CONTEXT, &tab1[*i], *opts);
	else
	{
		env_exec_call(CONTEXT, &tab1[*i], *opts);
		reset_stuff(CONTEXT, POISON);
		return (1);
	}
	return (0);
}

void					check_loop_env(char **tab1, t_env *e)
{
	int					i;
	int					ret;
	unsigned long		opts;

	i = 0;
	opts = 0;
	while (tab1[++i])
	{
		ret = m_l(0, &i, tab1, &opts);
		if (ret == 1)
			return ;
		else if (ret == 2)
			break ;
	}
	ft_print_env(e);
	reset_stuff(e, 0);
}
