/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:44:35 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 08:45:18 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void	cd_norm_part3(char **buf, char **tmp2, t_env *e)
{
	getcwd(*buf, 1000);
	if (!*buf)
		e->current = NULL;
	else
	{
		if (e->current)
			free(e->current);
		e->current = ft_strdup(*buf);
		tmp2[0] = "nothing";
		tmp2[1] = "OLDPWD";
		tmp2[2] = get_env("PWD", e->env, 1);
		if (!tmp2[2])
			tmp2[2] = ft_strdup(*buf);
		ft_setenv(tmp2, e);
		if (tmp2[2])
			free(tmp2[2]);
		tmp2[1] = "PWD";
		tmp2[2] = ft_strdup(*buf);
		ft_setenv(tmp2, e);
		if (tmp2[2])
			free(tmp2[2]);
	}
}

static	void	cd_norm_part2(t_env *e, char **tmp2, char *tmp3)
{
	if (!tmp3)
	{
		ft_putendl_fd("OLDPWD not set", 2);
		e->last_status = 1;
		return ;
	}
	tmp2[0] = get_env("HOME", e->env, 1);
	if (ft_strncmp(tmp3, tmp2[0], ft_strlen(tmp2[0])) == 0)
		;
	else
		ft_putendl(tmp3);
	if (chdir(tmp3) != 0)
	{
		e->last_status = 1;
		ft_putendl_fd("Unknown error", 2);
	}
	ft_memdel((void **)&e->cur_direc);
	e->cur_direc = ft_strdup(tmp3);
	if (tmp2[0])
		free(tmp2[0]);
	tmp2[0] = "ft_setenv";
	tmp2[2] = tmp3;
	ft_setenv(tmp2, e);
}

static	void	cd_norm_part1(char **tab1, t_env *e, char **tmp2, char *tmp3)
{
	tmp2[0] = "ft_setenv";
	tmp2[1] = "OLDPWD";
	tmp3 = get_env("OLDPWD", e->env, 1);
	tmp2[2] = get_env("PWD", e->env, 1);
	ft_setenv(tmp2, e);
	ft_memdel((void **)&tmp2[2]);
	tmp2[1] = "PWD";
	if (tab1[1][1] && tab1[1][1] == '-')
	{
		tmp2[2] = get_env("HOME", e->env, 1);
		ft_setenv(tmp2, e);
		if (chdir(tmp2[2]) != 0)
		{
			e->last_status = 1;
			ft_putendl_fd("Unknown error", 2);
		}
		if (tmp2[2])
			ft_memdel((void**)&tmp2[2]);
		ft_memdel((void **)&e->cur_direc);
		e->cur_direc = ft_strdup(tmp2[2]);
	}
	else if (ft_strlen(tab1[1]) == 1)
		cd_norm_part2(e, tmp2, tmp3);
	if (tmp3)
		ft_memdel((void**)&tmp3);
}

static	void	synthes_norm(char **tab1, t_env *e, char **tmp2, char *tmp3)
{
	char		*buf;
	char		*path;

	buf = (char *)ft_memalloc(sizeof(char) * 1024);
	path = get_back_path_link(e, tab1[1]);
	if (chdir(path ? path : tab1[1]) == -1)
	{
		if (ft_strncmp(tab1[1], "-", 1) == 0 && ft_strlen(tab1[1]) < 3)
			cd_norm_part1(tab1, e, tmp2, tmp3);
		else if (access(tab1[1], F_OK) == 0)
			builtin_setup_error("cd : permission denied ", e, 1);
		else
		{
			builtin_setup_error("invalid path : cd ", e, 1);
			ft_putendl_fd(tab1[1], 2);
		}
	}
	else
	{
		ft_memdel((void **)&e->cur_direc);
		cd_norm_part3(&buf, tmp2, e);
		e->cur_direc = ft_strdup(buf);
	}
	ft_memdel((void**)&buf);
	ft_memdel((void**)&path);
}

void			ft_cd(char **tab1, t_env *e)
{
	char			**tmp2;
	char			*tmp3;
	unsigned long	opts;
	int				ret;

	tmp2 = p_try(sizeof(char *) * 4, e);
	tmp3 = NULL;
	opts = 0;
	ret = 0;
	if (tab1[1] && !tab1[2] && (!(ret =
		check_opts(tab1[1], "LP", &opts, SET_OPTS | LAST_OPTS)) || ret == -1))
		synthes_norm(tab1, e, tmp2, tmp3);
	else if (ret && !tab1[2])
		builtin_setup_error(NULL, e, 0);
	else if (tab1[1] && tab1[2] && !tab1[3] && (!(ret =
		check_opts(tab1[1], "LP", &opts, SET_OPTS)) || ret == -1))
		cd_double_args(tab1, tmp2, tmp3, e);
	else if (ret)
		cd_with_opts(e, opts, tab1[2], tmp2);
	else if (tab1[1] && tab1[2] && tab1[3])
		builtin_setup_error("too many argument for command : cd ", e, 1);
	else if (tab1[0])
		cd_no_arg(tmp2, e);
	ft_memdel((void **)&tmp2);
}
