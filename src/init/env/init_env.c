/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 10:37:05 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 05:47:31 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void	set_cp(int i, char **env, t_env *e)
{
	char		**cp;

	if (!env)
	{
		(e->env) ? ft_del_tab(e->env) : 0;
		e->env = NULL;
		return ;
	}
	while (env[i])
		i++;
	i += 1;
	if ((cp = (char **)ft_memalloc(sizeof(char*) * i)) == NULL)
		display_error(-1, "malloc failed char *, exit", e);
	while (i)
	{
		cp[i] = NULL;
		i--;
	}
	i = -1;
	while (env[++i])
	{
		if (ft_strlen(env[i]) > 0)
			cp[i] = ft_strdup(env[i]);
	}
	e->env = cp;
}

static	void	set_init(t_env *e)
{
	t_cursor	*cursor;
	t_quote		*count;

	if ((cursor = (t_cursor *)ft_memalloc(sizeof(t_cursor))) == NULL)
		display_error(-1, "malloc failed struct t_cursor, exit", e);
	if ((count = (t_quote *)ft_memalloc(sizeof(t_quote))) == NULL)
		display_error(-1, "malloc failed struct t_quote, exit", e);
	count->bq = 0;
	count->pr = 0;
	count->ac = 0;
	e->count_qu = count;
	cursor->col = 0;
	cursor->row = 0;
	cursor->total = 0;
	e->cursor = cursor;
	ft_memset((void *)&(e->fd), -1, 12);
	ft_memset((void *)&(e->ag_fd), -1, 12);
	ft_memset((void *)&(e->std_fd), -1, 12);
	e->std_fd[0] = dup(STDIN_FILENO);
	e->std_fd[1] = dup(STDOUT_FILENO);
	e->std_fd[2] = dup(STDERR_FILENO);
	e->hshell = 0;
	e->term_fd = open(ctermid(NULL), O_RDWR);
	e->foreground = 1;
}

void			init_env(char **env, t_env *e)
{
	e->home = get_env("HOME", env, 1);
	e->flag_env = (env) ? 1 : 0;
	set_init(e);
	if (!e->home)
		e->home = ft_get_pwd();
	if (env)
		set_cp(0, env, e);
	if (e->env)
	{
		set_shlvl(e);
		set_sh(e);
		set_pwd(e);
		set_old_pwd(e);
		set_exe(e);
		set_hash(e);
	}
	else
		set_tmp_env(e);
	set_loc_var_env(e);
	update_ret_value(e);
}
