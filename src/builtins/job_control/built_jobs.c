/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_jobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:43:11 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int		ft_check_o(char *opts)
{
	int			ret;
	int			i;

	ret = 0;
	i = 1;
	if (!opts || opts[0] != '-' || ft_strlen(opts) < 2)
		return (0);
	while (opts[i])
	{
		if (opts[i] == 'l')
			ret = ret | FLAG_L;
		else if (opts[i] == 'n')
			ret = ret | FLAG_N;
		else if (opts[i] == 'p')
			ret = ret | FLAG_P;
		else if (opts[i] == 'r')
			ret = ret | FLAG_R;
		else if (opts[i] == 's')
			ret = ret | FLAG_S;
		else
			return (0);
		i++;
	}
	return (ret);
}

static	void	ft_norm_jobs(t_childs *tmp, t_env *e, int opt, int z)
{
	int			i;

	i = get_size_childs(e->childs);
	if (opt & FLAG_L)
		print_jobs_l(tmp, e, i, z);
	else if (opt & FLAG_P)
		print_jobs_p(tmp, e, i, z);
	else
		print_jobs_(tmp, e, i, z);
}

void			jobs_print__event(t_childs *tmp, t_sigevent event)
{
	if (!tmp)
		return ;
	ft_putstr_fd("[", 2);
	if (tmp->child)
		ft_putnbr_fd(tmp->child, 2);
	ft_putstr_fd("] ", 2);
	if (event == E_SIGSTOPPED)
		ft_putstr_fd("Stopped     ", 2);
	else if (event == E_SIGTERMINATED)
		ft_putstr_fd("Terminated	", 2);
	else if (event == E_DONE)
		ft_putstr_fd("Done			", 2);
	if (tmp->name)
		event == E_DONE ? ft_putstr_fd(tmp->name, 2)
			: ft_putendl_fd(tmp->name, 2);
}

void			ft_jobs(char **tab1, t_env *e)
{
	t_childs	*tmp;
	int			opt;
	int			z;

	tmp = e->childs;
	opt = 0;
	if (tab1 && tab1[0] && tab1[1] && !tab1[2] && (opt = ft_check_o(tab1[1])))
		;
	else if (tab1[1])
		return ;
	z = 1;
	if (!tmp)
		return ;
	else
		ft_norm_jobs(tmp, e, opt, z);
}
