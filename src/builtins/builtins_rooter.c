/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_rooter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:44:23 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 06:59:47 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int		check_bord_var(char **array)
{
	char		*cut;
	char		save;
	int			ret;

	if (!array || !array[0] || array[0][0] == '=')
		return (0);
	if (!(cut = ft_strchr(array[0], '=')))
		return (0);
	ret = 1;
	save = cut[1];
	cut[1] = 0;
	if (check_before_equal(array[0], "\'\"\""))
		ret = 0;
	cut[1] = save;
	return (ret);
}

static int		built_exec(char **array, t_env *e, const t_builtins *builtins)
{
	int		index;

	index = 0;
	if (!builtins)
		return (0);
	while (builtins[index].builtin_name != NULL)
	{
		if (ft_strcmp(builtins[index].builtin_name, array[0]) == 0)
		{
			builtins[index].builtin_func(array, e);
			return (1);
		}
		index++;
	}
	if (check_bord_var(array))
	{
		ft_built_var(array, e);
		return (1);
	}
	return (0);
}

static int		built_exists(char **array, const t_builtins *builtins)
{
	int		index;

	index = 0;
	if (!builtins)
		return (0);
	while (builtins[index].builtin_name != NULL)
	{
		if (ft_strcmp(builtins[index].builtin_name, array[0]) == 0)
			return (1);
		index++;
	}
	if (check_bord_var(array))
		return (1);
	return (0);
}

static	t_builtins	const	g_builtins[] =
{
	{"exit", &check_exit},
	{"setenv", &ft_setenv},
	{"env", &check_loop_env},
	{"unsetenv", &ft_unsetenv},
	{"cd", &ft_cd},
	{"fg", &built_fg},
	{"bg", &built_bg},
	{"jobs", &ft_jobs},
	{"echo", &ft_echo},
	{"export", &ft_export},
	{"pwd", &ft_pwd},
	{"history", &built_history},
	{"unset", &ft_unset},
	{"read", &ft_read},
	{NULL, NULL}
};

int				get_builtin(char **array, t_env *e, t_fexec exec)
{
	if (exec == EXEC)
		return (built_exec(array, e, g_builtins));
	else
		return (built_exists(array, g_builtins));
}
