/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:56:25 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void		norm_set_getfull(t_agreg *ag)
{
	ag->right = ft_strjoin(ag->left, " ");
	free(ag->left);
	ag->left = ft_strjoin(ag->right, ag->spliter);
	free(ag->right);
	ag->right = NULL;
}

void				get_full_redir_r(t_token *node, t_agreg *ag)
{
	t_token			*tmp;
	char			**splited;

	tmp = node;
	while (tmp && check_type_redir(tmp) == 1)
	{
		if (tmp->second)
		{
			splited = ft_strsplit_spec(tmp->second, 0);
			if (splited[1])
			{
				ag->spliter = ft_implode(&splited[1], ' ');
				if (ag->left)
					norm_set_getfull(ag);
				else
					ag->left = ft_strdup(ag->spliter);
				ft_memdel((void**)&(ag->spliter));
			}
			free(tmp->second);
			tmp->second = ft_strdup(splited[0]);
			(splited) ? ft_del_tab(splited) : 0;
		}
		tmp = tmp->previous;
	}
	splited = NULL;
}

int					check_type_redir(t_token *node)
{
	int				a;

	a = node->type;
	if (a == R_REDIR || a == R_D_REDIR || a == L_REDIR)
		return (1);
	else if (a == AND_RE || a == OR_RE)
		return (1);
	else if (a == R_A_RED || a == L_AGR_REDIR)
		return (1);
	return (0);
}
