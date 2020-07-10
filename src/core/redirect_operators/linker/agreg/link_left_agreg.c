/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_left_agreg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 09:44:34 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int			linker_right_a(t_token *node, t_agreg *t, t_env *e)
{
	int				fd;
	char			*trimed;

	trimed = ft_strtrim(node->second);
	if ((fd = open(trimed, (O_RDWR | O_CREAT | O_TRUNC), get_rights())) == -1)
		node->errno_node = ft_strjoin(trimed, ERROR_RW_FILE);
	else
	{
		e->fd[0] = fd;
		node->fd = fd;
		node->type = R_REDIR;
		(trimed) ? free(trimed) : (void)trimed;
		reset_agreg(t, 1);
		return (0);
	}
	(trimed) ? free(trimed) : (void)trimed;
	reset_agreg(t, 1);
	return (-1);
}

static	void		norm_setlink_ra(t_token *node, t_agreg *t)
{
	t->spliter = ft_strdup(node->tok);
	t->cut = ft_strchr(t->spliter, '<');
	if (t->spliter && t->spliter[0] != '<')
	{
		t->cut[0] = 0;
		t->left = ft_strdup(t->spliter);
		t->cut[0] = '<';
	}
	(t->cut[2]) ? t->right = ft_strtrim(&t->cut[2]) : 0;
	t->left_val = (t->left) ? ft_atoi(t->left) : 1;
}

static	int			norm_linkerr_ra(t_token *node, t_agreg *t, int opt)
{
	if (!opt)
		node->errno_node = ft_strjoin(node->second, ERR_AMB);
	else
		node->errno_node = ft_strjoin(t->right, ERR_FD);
	reset_agreg(t, 1);
	return (-1);
}

static	void		set_fd_ra(t_agreg *t, t_env *e)
{
	if (t->right_val == 1)
		e->ag_fd[0] = t->left_val;
	if (t->left_val == 1)
		e->ag_fd[1] = t->right_val;
}

int					link_left_agreg(t_token *node, t_env *e)
{
	t_agreg			*t;

	if (node->errno_node)
		return (-1);
	t = set_agreg();
	norm_setlink_ra(node, t);
	t->right_val = (t->right) ? ft_atoi(t->right) : 0;
	if (!t->right && t->left_val > 1)
		return (norm_linkerr_ra(node, t, 0));
	if ((!t->left || t->left_val == 1) && !t->right)
		return (linker_right_a(node, t, e));
	else
	{
		(strchr(t->right, '-') != NULL) ? t->close = 1 : 0;
		if (t->close == 1 && ft_strlen(&t->cut[2]) == 1)
			close(t->left_val);
		else if (t->right_val != 0 && t->right_val && t->close == 1)
			close(t->right_val);
		else if (FD_T_R != FD_T_L && (t->left_val == 1 || t->right_val == 1))
			set_fd_ra(t, e);
		else if (FD_T_R != FD_T_L && (dup2(t->right_val, t->left_val) == -1))
			return (norm_linkerr_ra(node, t, 1));
	}
	reset_agreg(t, 1);
	return (0);
}
