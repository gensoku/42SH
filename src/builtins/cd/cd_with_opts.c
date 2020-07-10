/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_with_opts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 10:15:14 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 07:44:11 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void	link_detected(t_env *e, char *cmd, char **wtf, char *tmp_pwd)
{
	char		*where;

	where = where_are_we();
	tmp_pwd = ft_strnew(ft_strlen(where) + ft_strlen(cmd) + 1);
	ft_strcat(tmp_pwd, where);
	ft_strcat(tmp_pwd, "/");
	ft_strcat(tmp_pwd, cmd);
	wtf[0] = "setenv";
	ft_memdel((void **)&wtf[1]);
	wtf[1] = "OLDPWD";
	wtf[2] = get_env("PWD", e->local_env ? e->local_env : e->env, CASE_TRUE);
	if (!wtf[2])
		wtf[2] = ft_strdup(e->cur_direc);
	ft_setenv(wtf, e);
	ft_memdel((void **)&e->cur_direc);
	ft_memdel((void **)&wtf[2]);
	e->cur_direc = ft_strdup(tmp_pwd);
	wtf[0] = "setenv";
	wtf[1] = ft_strdup("PWD");
	wtf[2] = (e->cur_direc) ? ft_strdup(e->cur_direc) : ft_get_pwd();
	wtf[3] = NULL;
	ft_setenv(wtf, e);
	builtin_setup_error(NULL, e, 0);
	ft_memdel((void **)&where);
	ft_memdel((void **)&wtf[2]);
}

static	void	cd_opts_link(t_env *e, char *cmd, char **wtf, char *tmp_pwd)
{
	if (g_sts_f(cmd, F_GET_TYPE) == F_DIR)
		ft_cd(wtf, e);
	else if (g_sts_f(cmd, F_GET_TYPE) == F_SYMLINK)
	{
		if (g_sts_f(cmd, F_GETLNK_TYPE) != F_DIR)
		{
			ft_putstr_fd("cd : not a directory : ", 2);
			builtin_setup_error(cmd, e, 1);
		}
		else
		{
			if (chdir(cmd) != 0)
			{
				builtin_setup_error("cd : Unknown error", e, 1);
				return ;
			}
			link_detected(e, cmd, wtf, tmp_pwd);
		}
	}
	else
	{
		ft_putstr_fd("cd : Not a directory :", 2);
		builtin_setup_error(cmd, e, 1);
	}
}

void			cd_with_opts(t_env *e, unsigned long opts,
	char *cmd, char **wtf)
{
	char		buf[BUFF_SIZE];

	ft_bzero(&buf, BUFF_SIZE);
	wtf[0] = "Si tu comprend ca t'est serieux";
	wtf[2] = NULL;
	if (!cmd || !opts)
	{
		builtin_setup_error("Internal error on command : cd", e, 1);
		return ;
	}
	wtf[1] = ft_strdup(cmd);
	if (is_opt_set(opts, 'P') || !is_opt_set(opts, 'L'))
		ft_cd(wtf, e);
	else
		cd_opts_link(e, cmd, wtf, NULL);
	ft_memdel((void **)&wtf[1]);
	ft_memdel((void **)&wtf[2]);
}
