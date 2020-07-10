/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_launcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 02:48:13 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/16 10:54:22 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void	convert_double_left(t_token *node, t_env *e, char *tmp, int i)
{
	char		*trimed;

	trimed = ft_itoa(i);
	tmp = ft_strjoin(TEMPO, trimed);
	(trimed) ? ft_memdel((void **)&trimed) : 0;
	trimed = ft_strtrim(node->second);
	push_back_redir(e, trimed, tmp);
	(trimed) ? ft_memdel((void **)&trimed) : 0;
	(node->tok) ? ft_memdel((void **)&node->tok) : 0;
	(node->second) ? ft_memdel((void **)&node->second) : 0;
	node->tok = ft_strdup("<");
	node->second = ft_strdup(tmp);
	node->type = L_REDIR;
	(tmp) ? ft_memdel((void **)&tmp) : 0;
}

int				heredoc_launcher(t_token *node, t_env *e, int i)
{
	char		*tmp;
	t_redir		*tmp2;

	tmp = NULL;
	if (!node)
	{
		if (e->left_redir)
		{
			tmp2 = e->left_redir;
			while (tmp2)
				tmp2 = tmp2->next;
			return (read_display_2(0, e, e->left_redir));
		}
		return (0);
	}
	if (node->tok && node->type == L_D_REDIR)
	{
		if (!node->first && !node->next)
			node->first = ft_strdup("cat");
		convert_double_left(node, e, tmp, i);
		i++;
	}
	return (heredoc_launcher(node->previous, e, i));
}
