/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unsetenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:46:11 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/12 10:46:12 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void	norm_copy_assign_env(char **tab1, t_env *e, char **env2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (e->env[i])
	{
		if (ft_strncmp(tab1[1], e->env[i], ft_strlen(tab1[1])) != 0
			|| ft_strchr(tab1[1], '=') != NULL)
		{
			env2[j] = ft_strdup(e->env[i]);
			j++;
		}
		i++;
	}
	env2[i] = NULL;
	(e->env) ? ft_del_tab(e->env) : 0;
	remove_var(tab1[1]);
	e->env = env2;
}

void			ft_unsetenv(char **tab1, t_env *e)
{
	int			i;
	char		**env2;

	i = 0;
	if (!e->env)
		return ;
	if (!tab1 || !tab1[1] || tab1[2])
	{
		if (!tab1[1])
		{
			e->last_status = 1;
			ft_putendl_fd("error: usage : unsetenv name.", 2);
		}
		return ;
	}
	while (e->env[i])
		i++;
	if ((env2 = (char **)ft_memalloc(sizeof(char *) * i + 1)) == NULL)
		display_error(-1, "malloc failed char **, exit", e);
	norm_copy_assign_env(tab1, e, env2);
}
