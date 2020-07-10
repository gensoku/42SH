/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_replace_tild.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 08:46:45 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/22 01:13:51 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void	free_assign(char *to_assign, char **to_free)
{
	ft_memdel((void **)to_free);
	if (!to_assign)
		return ;
	*to_free = to_assign;
}

void			checks_tild(char *str, t_env *e, char **to_free)
{
	char		*tmp;
	char		*tmp2;

	if (!str)
		;
	if (str[0] && str[0] == '~')
	{
		tmp = get_env("HOME", e->env, 1);
		if (!tmp)
			tmp = ft_strdup(e->home);
		tmp2 = ft_strjoin(tmp, &str[1]);
		if (tmp)
			free(tmp);
		tmp = NULL;
		free_assign(tmp2, to_free);
	}
	else
	{
		tmp2 = ft_strdup(str);
		free_assign(tmp2, to_free);
	}
}
