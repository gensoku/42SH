/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_setenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:45:58 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 07:09:57 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void	ft_put_eol(char *val)
{
	while (*val)
	{
		if (*val == '\n')
			ft_putstr_fd("\\n", 2);
		else
			ft_putchar_fd(*val, 2);
		val++;
	}
}

static	size_t	count_to_chr(char *str, char c)
{
	size_t i;

	i = 0;
	if (!str || !c)
		return (0);
	while (str[i])
	{
		if (str[i] != c)
			i++;
		else
			return (i);
	}
	return (0);
}

static	int		norm_setenv(char **tab1, t_env *e)
{
	int i;

	i = 0;
	if (!tab1 || !tab1[1] || !tab1[2] || (tab1[3] && ft_strlen(tab1[3]) > 0))
	{
		e->last_status = 1;
		ft_putendl_fd("usage : setenv [name] [value].", 2);
		return (-1);
	}
	else if ((ft_strchr(tab1[2], '\n') != NULL) || !ft_strlen(tab1[1]) ||
		!ft_strlen(tab1[2]) || tab1[1][0] == '=' || tab1[2][0] == '=')
	{
		e->last_status = 1;
		ft_putstr_fd("setenv: not valid in this context: ", 2);
		ft_put_eol((LEN_(tab1[1]) && tab1[1][0] == '=') ? tab1[1] : tab1[2]);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	if (!e->env)
		return (1);
	while (e->env[i])
		i++;
	return (i);
}

static	void	norm_setenv2(char **tab1, char *tmp, char **env2, int i)
{
	while (CTX(env)[++i])
	{
		if (ft_strncmp(tab1[1], CTX(env)[i], ft_strlen(tab1[1])) != 0 ||
			ft_strlen(tab1[1]) != count_to_chr(CTX(env)[i], '='))
			env2[i] = ft_dup_free(env2[i], CTX(env)[i]);
		else
		{
			tmp = ft_strjoin(tab1[1], "=");
			env2[i] = ft_strjoin(tmp, tab1[2]);
		}
	}
	if (!tmp)
	{
		tmp = ft_strjoin(tab1[1], "=");
		env2[i] = ft_strjoin(tmp, tab1[2]);
		(!(update_var(tab1[1], tab1[2], CONTEXT))) ?
			set_var_(env2[i], ENV_VAR, VAR_X) : 0;
		i++;
	}
	env2[i] = NULL;
	ft_memdel((void**)&tmp);
	update_var(tab1[1], tab1[2], CONTEXT);
	(CTX(env)) ? ft_del_tab(CTX(env)) : 0;
	CTX(env) = &env2[0];
}

void			ft_setenv(char **tab1, t_env *e)
{
	char		**env2;
	int			i;

	i = norm_setenv(tab1, e);
	if (i == -1)
		return ;
	if ((env2 = (char **)ft_memalloc(sizeof(char *) * i + 3)) == NULL)
		display_error(-1, "malloc failed char *, exit", e);
	norm_setenv2(tab1, NULL, env2, -1);
	(tab1 && tab1[1] && !ft_strcmp(tab1[1], "PATH")) ? set_exe(e) : 0;
	(tab1 && tab1[1] && !ft_strcmp(tab1[1], "PATH")) ? set_hash(e) : 0;
}
