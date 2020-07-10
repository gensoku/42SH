/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_sh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 05:42:18 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 05:47:58 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	set_tmp_env(t_env *e)
{
	char **tmp_env;
	char *pwd;

	if ((tmp_env = (char **)malloc(sizeof(char *) * 5)) == NULL)
		display_error(-1, "malloc failed intern char **(env), exit", e);
	pwd = ft_get_pwd();
	tmp_env[0] = ft_strjoin("SHELL=", SH_NAME);
	tmp_env[1] = ft_strdup("SHLVL=2");
	tmp_env[2] = ft_strjoin("PWD=", pwd);
	tmp_env[3] = ft_strjoin("OLDPWD=", pwd);
	tmp_env[4] = NULL;
	e->env = tmp_env;
	ft_memdel((void **)&pwd);
}

void	set_pwd(t_env *e)
{
	char **pwd;

	if ((pwd = (char **)ft_memalloc(sizeof(char *) * 4)) == NULL)
		display_error(-1, "malloc failed intern char **(env), exit", e);
	pwd[0] = "1";
	pwd[1] = "PWD";
	pwd[2] = ft_get_pwd();
	pwd[3] = NULL;
	ft_setenv(pwd, e);
	if (pwd[2] && ft_strlen(pwd[2]) > 0)
	{
		free(pwd[2]);
		pwd[2] = NULL;
	}
	free(pwd);
}

void	set_old_pwd(t_env *e)
{
	char **opwd;

	if ((opwd = (char **)malloc(sizeof(char *) * 4)) == NULL)
		display_error(-1, "malloc failed intern char **(env), exit", e);
	opwd[0] = "2";
	opwd[1] = "OLDPWD";
	opwd[2] = ft_get_pwd();
	opwd[3] = NULL;
	ft_setenv(opwd, e);
	if (opwd[2] && ft_strlen(opwd[2]) > 0)
	{
		free(opwd[2]);
		opwd[2] = NULL;
	}
	free(opwd);
}

void	set_shlvl(t_env *e)
{
	char **shlvl;
	char *tmp;

	if ((shlvl = (char **)malloc(sizeof(char *) * 4)) == NULL)
		display_error(-1, "malloc failed char *, exit", e);
	shlvl[0] = "3";
	shlvl[1] = "SHLVL";
	tmp = get_env("SHLVL", e->env, 1);
	if (!tmp)
		shlvl[2] = "2";
	else
		shlvl[2] = ft_itoa(ft_atoi(tmp) + 1);
	shlvl[3] = NULL;
	ft_setenv(shlvl, e);
	if (tmp && ft_strlen(tmp) > 0)
	{
		free(shlvl[2]);
		shlvl[2] = NULL;
	}
	(tmp) ? ft_memdel((void**)&tmp) : (void)tmp;
	free(shlvl);
}

void	set_sh(t_env *e)
{
	char **sh_name;

	if ((sh_name = (char **)malloc(sizeof(char *) * 4)) == NULL)
		display_error(-1, "malloc failed char *, exit", e);
	sh_name[0] = "4";
	sh_name[1] = "SHELL";
	sh_name[2] = SH_NAME;
	sh_name[3] = NULL;
	ft_setenv(sh_name, e);
	free(sh_name);
}
