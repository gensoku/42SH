/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_left_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:56:10 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int		norm_errlink_lr(t_token *node, t_agreg *t, char *str, int opt)
{
	if (!opt)
	{
		if (!node->errno_node)
			node->errno_node = ft_strjoin(node->second, ERROR_R_FILE);
		reset_agreg(t, 1);
		(str) ? ft_memdel((void**)&str) : 0;
	}
	else
	{
		t->cut[0] = 0;
		if (!node->errno_node)
			node->errno_node = ft_strjoin(node->tok, ERR_FD);
		t->cut[0] = '<';
		reset_agreg(t, 1);
	}
	return (-1);
}

static	int		catch_a_line(int fd, t_token *node, t_agreg *t, char *trimed)
{
	close(fd);
	return (norm_errlink_lr(node, t, trimed, 1));
}

int				link_tok_left(t_token *node, t_env *e)
{
	int			fd;
	char		*trimed;
	t_agreg		*t;

	t = set_agreg();
	t->left_val = STDIN_FILENO;
	t->cut = ft_strchr(node->tok, '<');
	if (node->tok[0] && node->tok[0] != '<')
	{
		t->cut[0] = 0;
		t->left_val = ft_atoi(node->tok);
		t->cut[0] = '<';
	}
	trimed = ft_strtrim(node->second);
	if ((fd = open(trimed, O_RDONLY)) == -1)
		return (norm_errlink_lr(node, t, trimed, 0));
	if (t->left_val != 0 && dup2(t->left_val, fd) == -1)
		return (catch_a_line(fd, node, t, trimed));
	else if (t->left_val == 0)
		e->fd[2] = fd;
	node->fd = fd;
	(trimed) ? free(trimed) : (void)trimed;
	reset_agreg(t, 1);
	return (0);
}
