/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_double_right_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:56:27 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int			norm_err_drr(t_token *node, t_agreg *t, char **splited)
{
	(node->errno_node) ? free(node->errno_node) : 0;
	node->errno_node = ft_strjoin(splited[0], ERROR_RW_FILE);
	reset_agreg(t, 1);
	ft_del_tab(splited);
	return (-1);
}

int					run_tok_right2(t_token *node)
{
	int				fd;
	t_agreg			*t;
	char			**splited;

	splited = ft_strsplit_spec(node->second, 0);
	if (!node || !splited || !splited[0])
		return (-1);
	t = set_agreg();
	if ((fd = open(splited[0], (O_RDWR | O_CREAT | O_APPEND),
	get_rights())) == -1)
		return (norm_err_drr(node, t, splited));
	if (!node->next || check_type_redir(node->next) == 0)
	{
		get_full_redir_r(node, t);
		if (t->left)
		{
			t->right = ft_strjoin(node->first, " ");
			free(node->first);
			node->first = ft_strjoin(t->right, t->left);
		}
	}
	reset_agreg(t, 1);
	ft_del_tab(splited);
	close(fd);
	return (0);
}
