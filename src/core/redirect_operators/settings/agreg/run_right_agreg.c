/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_right_agreg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 09:36:48 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int		norm_err_rag(t_token *node, t_agreg *t, int opt)
{
	if (!opt)
	{
		if (node->errno_node)
			free(node->errno_node);
		node->errno_node = ft_strjoin(node->second, ERR_RAG);
		reset_agreg(t, 1);
	}
	else
	{
		if (node->errno_node)
			free(node->errno_node);
		node->errno_node = ft_strjoin(node->second, ERR_AMB);
		reset_agreg(t, 1);
	}
	return (-1);
}

static	void	norm_set_rag(t_token *node, t_agreg *t)
{
	(t->left) ? ft_memdel((void**)&(t->left)) : 0;
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
}

int				run_right_agreg(t_token *node, t_env *e)
{
	t_agreg		*t;

	t = set_agreg();
	(void)e;
	t->spliter = ft_strdup(node->tok);
	t->cut = ft_strchr(t->spliter, '>');
	if (t->spliter && t->spliter[0] != '>')
	{
		t->cut[0] = 0;
		t->left = ft_strdup(t->spliter);
		t->cut[0] = '>';
	}
	(t->cut[2]) ? t->right = ft_strtrim(&t->cut[2]) : 0;
	t->left_val = (t->left) ? ft_atoi(t->left) : 1;
	if ((!t->left || t->left_val == 1) && !t->right)
	{
		if (run_tok_right(node) == -1)
			return (norm_err_rag(node, t, 0));
	}
	else if (!t->right && t->left_val > 1)
		return (norm_err_rag(node, t, 1));
	else
		norm_set_rag(node, t);
	reset_agreg(t, 1);
	return (0);
}
