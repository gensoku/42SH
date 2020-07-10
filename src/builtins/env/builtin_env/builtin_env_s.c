/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 05:48:54 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/23 06:09:36 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int				check_valid_s_args(char **splited, t_env *e)
{
	int					i;
	char				*chr;

	if (!splited)
	{
		e->last_status = -1;
		return (1);
	}
	i = -1;
	while (splited[++i])
	{
		if ((chr = ft_strchr(splited[i], '=')))
		{
			chr[0] = 0;
			if (CHECK_SL(splited[i], ft_strlen(splited[i] - 1)) != 0)
			{
				ft_putendl_fd("env : Invalid sequence '\\=' in -S", 2);
				e->last_status = 1;
				chr[0] = '=';
				return (1);
			}
			chr[0] = '=';
		}
	}
	return (0);
}

static	void			opt_s_verbose_helper(char **splited, int i, char *str)
{
	ft_putstr_fd("#env  split -S: ", 2);
	ft_putendl_fd(str, 2);
	while (splited[i])
	{
		(!i) ? ft_putstr_fd("#env      into: ", 2) :
			ft_putstr_fd("#env          & ", 2);
		ft_putendl_fd(splited[i], 2);
		i++;
	}
}

static	int				opts_s_helper(char **splited, int i,
		unsigned long *opts, t_env *e)
{
	if (ft_strchr(splited[i], '='))
	{
		add_to_local_env(e, &splited[i], *opts);
		return (0);
	}
	else if (get_builtin(&splited[i], e, NO_EXEC) == 1)
	{
		e->last_status = env_bui_call(e, &splited[i], *opts);
		verbose_lvl(RESET_VERBOSE);
		e->envi = 0;
	}
	else
	{
		env_exec_call(e, &splited[i], *opts);
		e->envi = 0;
		verbose_lvl(RESET_VERBOSE);
	}
	return (1);
}

int						env_opt_s(t_env *e, char *str, unsigned long *opts)
{
	char				**splited;
	char				*trimed;
	int					i;

	if (!e || !str)
		return (4);
	trimed = (str && (str[0] == '\"' || str[0] == '\'')) ?
		ft_strsub(str, 1, ft_strlen(str)) : ft_strdup(str);
	splited = ft_strsplit_spec(trimed, 0);
	if (!splited)
		return (4);
	if (check_valid_s_args(splited, e))
		return (4);
	if (is_opt_set(*opts, 'v') && verbose_lvl(2) > 1)
		opt_s_verbose_helper(splited, 0, str);
	i = -1;
	while (splited[++i])
	{
		if (opts_s_helper(splited, i, opts, e))
			return (1);
	}
	check_opts("-S", "S", opts, 0 | SUPR_OPTS);
	ft_memdel((void **)&trimed);
	return (0);
}
