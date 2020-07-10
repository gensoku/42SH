/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:45:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 07:05:34 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

#define PWD_UK_ERR	"Unknown error on pwd, unable to locate current directory"

static	void			pwd_no_arg(t_env *e)
{
	char				*tmp;

	tmp = NULL;
	if ((tmp = get_env("PWD", e->local_env ? e->local_env : e->env, CASE_TRUE)))
		ft_putendl_fd(tmp, (e->fd[0] == -1) ? 1 : e->fd[0]);
	else if (e->cur_direc)
		ft_putendl_fd(e->cur_direc, (e->fd[0] == -1) ? 1 : e->fd[0]);
	else if ((tmp = ft_get_pwd()))
		ft_putendl_fd(tmp, (e->fd[0] == -1) ? 1 : e->fd[0]);
	else
	{
		builtin_setup_error(PWD_UK_ERR, e, 1);
		return ;
	}
	builtin_setup_error(NULL, e, 0);
	ft_memdel((void **)&tmp);
}

static	void			print_fd_free(char *print, char **to_free, int fd)
{
	ft_putendl_fd(print, fd);
	ft_memdel((void **)to_free);
	builtin_setup_error(NULL, CONTEXT, 0);
}

void					ft_pwd(char **tab1, t_env *e)
{
	unsigned long		opts;
	char				*tmp;

	opts = 0;
	if (!tab1 || !tab1[0])
		return ;
	else if (ft_len_tab(tab1) > 2)
		builtin_setup_error("pwd : too many arguments", e, 1);
	if (tab1[1] && (!check_opts(tab1[1], "LP", &opts, SET_OPTS | LAST_OPTS) ||
		check_opts(tab1[1], "LP", &opts, SET_OPTS | LAST_OPTS) == -1))
		builtin_setup_error("pwd : too many arguments", e, 1);
	else if (!tab1[1] || is_opt_set(opts, 'L'))
		pwd_no_arg(e);
	else if (is_opt_set(opts, 'P'))
	{
		if (!(tmp = ft_get_pwd()))
			builtin_setup_error("pwd : Unknown error", e, 1);
		else
			print_fd_free(tmp, &tmp, (e->fd[0] == -1) ? 1 : e->fd[0]);
	}
	else
		builtin_setup_error("pwd : Unknown error", e, 1);
}

char					*ft_get_pwd(void)
{
	char				*buf;
	char				*ret;

	buf = ft_strnew(BUFF_SIZE);
	ret = NULL;
	if (getcwd(buf, BUFF_SIZE - 1))
		ret = ft_strdup(buf);
	ft_memdel((void **)&buf);
	return (ret);
}
