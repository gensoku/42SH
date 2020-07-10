/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_part_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:44:44 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 08:56:35 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

char				*get_back_path_link(t_env *e, char *arg)
{
	char			*where;

	if (!arg)
		return (NULL);
	(void)e;
	where = where_are_we();
	if (is_relative_path(arg) && where &&
		g_sts_f(where, F_GET_TYPE) == F_SYMLINK)
	{
		where = get_relative_slash(arg, where);
		if (where)
			return (where);
		else
			return (NULL);
	}
	ft_memdel((void **)&where);
	return (NULL);
}

static void			display_norm_err(char *str, t_env *e)
{
	e->last_status = 1;
	ft_putstr_fd("cd : string not in pwd : ", 2);
	ft_putendl_fd(str, 2);
}

void				cd_no_arg(char **tmp2, t_env *e)
{
	tmp2[0] = "nothing";
	tmp2[1] = get_env("HOME", e->env, 1);
	if (!tmp2[1])
		tmp2[1] = ft_strdup(e->home);
	tmp2[2] = NULL;
	ft_cd(tmp2, e);
	if (tmp2[1])
		free(tmp2[1]);
}

void				cd_double_args(char **tab1, char **tmp2,
	char *tmp3, t_env *e)
{
	char			*tmp4;
	int				i;

	i = 0;
	tmp3 = get_env("PWD", e->env, 1);
	tmp2[1] = ft_strstr(tmp3, tab1[1]);
	if (!tmp2[1])
		display_norm_err(tab1[1], e);
	else
	{
		i = ft_strlen(tmp2[1]);
		tmp3[ft_strlen(tmp3) - i] = '\0';
		tmp2[2] = ft_strjoin(tmp3, tab1[2]);
		tmp2[1] += ft_strlen(tab1[1]);
		tmp4 = ft_strjoin(tmp2[2], tmp2[1]);
		tmp2[1] = ft_strdup(tmp4);
		(tmp2[2]) ? free(tmp2[2]) : (void)tmp2[2];
		tmp2[2] = NULL;
		tmp2[0] = "nothing";
		ft_cd(tmp2, e);
		(tmp2[1]) ? free(tmp2[1]) : (void)tmp2[1];
		(tmp4) ? free(tmp4) : (void)tmp4;
	}
	ft_memdel((void **)&tmp3);
}
