/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display_p.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:47:19 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			display_var_no_p(void)
{
	t_loc_var	*tmp;

	tmp = CTX(all_var);
	while (tmp)
	{
		if (tmp->type == TMP_VAR || tmp->type == ENV_VAR)
		{
			ft_putstr(tmp->key);
			ft_putstr("=");
			(tmp->value) ? ft_putendl(tmp->value) : ft_putendl("\'\'");
		}
		tmp = tmp->next;
	}
}

static	void	helper_var_p_opt(void)
{
	t_loc_var	*tmp;

	tmp = CTX(all_var);
	while (tmp)
	{
		if (tmp->type == TMP_VAR || tmp->type == ENV_VAR)
			display_var_p(tmp->key, 0);
		tmp = tmp->next;
	}
}

static	void	helper_var_p(t_loc_var *tmp)
{
	int			fd;

	fd = (CTX(fd)[0] == -1) ? 1 : CTX(fd)[0];
	ft_putstr_fd("typeset ", fd);
	(tmp->status && tmp->status != VAR_NEUTRAL) ? ft_putstr_fd("-", fd) : 0;
	(tmp->status & VAR_X) ? ft_putstr_fd("x", fd) : 0;
	(tmp->status & VAR_R) ? ft_putstr_fd("r", fd) : 0;
	(tmp->status) ? ft_putstr_fd(" ", fd) : 0;
	ft_putstr_fd(tmp->key, fd);
	ft_putstr_fd("=", fd);
	(tmp->value) ? ft_putendl_fd(tmp->value, fd) : ft_putendl_fd("\'\'", fd);
}

void			display_var_p(char *key, int opt)
{
	t_loc_var	*tmp;
	char		*cut;

	if (opt)
		helper_var_p_opt();
	else
	{
		cut = ft_strchr(key, '=');
		if (cut)
		{
			cut[0] = 0;
			tmp = get_var_ptr(CONTEXT, key, CASE_TRUE);
			cut[0] = '=';
			if (!tmp)
				return ;
		}
		else if (!(tmp = get_var_ptr(CONTEXT, key, CASE_TRUE)))
			return ;
		helper_var_p(tmp);
	}
}
