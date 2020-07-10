/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_right_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/19 09:31:49 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int		norm_linkerr_ra_(t_token *node, t_agreg *t, int opt, char *tr)
{
	if (!opt)
		node->errno_node = ft_strjoin(node->second, ERROR_RW_FILE);
	else
	{
		t->cut[0] = 0;
		node->errno_node = ft_strjoin(node->tok, ERR_FD);
		t->cut[0] = '>';
	}
	(tr) ? ft_memdel((void**)&tr) : 0;
	reset_agreg(t, 1);
	return (-1);
}

static	int		set_fd_ra(int val, int fd, t_agreg *t, t_env *e)
{
	if (val == 1)
		e->fd[0] = fd;
	else if (val == 2)
		e->fd[1] = fd;
	else if (val > 2 && (dup2(fd, t->left_val) == -1))
		return (-1);
	return (0);
}

int				link_tok_right(t_token *node, t_env *e)
{
	int				fd;
	char			*trimed;
	t_agreg			*t;

	t = set_agreg();
	t->left_val = STDOUT_FILENO;
	t->cut = ft_strchr(node->tok, '>');
	if (node->tok[0] && node->tok[0] != '>')
	{
		t->cut[0] = 0;
		t->left_val = ft_atoi(node->tok);
		t->cut[0] = '>';
	}
	trimed = ft_strtrim(node->second);
	if ((fd = open(trimed, O_RDWR | O_SYNC)) == -1)
		return (norm_linkerr_ra_(node, t, 0, trimed));
	if (set_fd_ra(t->left_val, fd, t, e) == -1)
	{
		close(fd);
		return (norm_linkerr_ra_(node, t, 1, trimed));
	}
	node->fd = fd;
	(trimed) ? free(trimed) : (void)trimed;
	reset_agreg(t, 1);
	return (0);
}
