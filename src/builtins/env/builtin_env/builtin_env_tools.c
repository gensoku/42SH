/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 05:39:58 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/22 08:31:31 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void				ft_print_env(t_env *e)
{
	int				i;

	i = 0;
	if ((!e->env && !e->local_env) || e->envi)
		return ;
	if (e->local_env)
		ft_put_tab_fd(e->local_env, (e->fd[0] == -1) ? 1 : e->fd[0], '\n');
	else if (e->env && e->env[i])
		ft_put_tab_fd(e->env, (e->fd[0] == -1) ? 1 : e->fd[0], '\n');
	(e->local_env) ? ft_del_tab(e->local_env) : 0;
	e->local_env = NULL;
}

int					verbose_lvl(int option)
{
	static	int		ret = 0;

	if (!option)
		ret++;
	(option == RESET_VERBOSE) ? ret = 0 : 0;
	return (ret);
}

void				display_verbose_lvl(int nb)
{
	while (nb)
	{
		if (verbose_lvl(2) > 0)
		{
			ft_putstr_fd("#env verbosity now at : ", 2);
			ft_putnbr_fd(verbose_lvl(0), 2);
			ft_putchar_fd('\n', 2);
		}
		else
			verbose_lvl(0);
		nb--;
	}
}

int					how_many_char(char *str, char c)
{
	int				ret;
	int				i;

	if (!str)
		return (0);
	ret = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			ret++;
	}
	return (ret);
}
