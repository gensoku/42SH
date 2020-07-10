/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:58:45 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void				destructor_file(t_redir *list, t_env *e)
{
	t_redir			*tmp;
	char			*rm_path;
	int				fd;

	tmp = list;
	while (tmp)
	{
		fd = open(tmp->path, O_RDONLY);
		if (fd != -1)
		{
			rm_path = ft_strjoin("rm ", tmp->path);
			exec_tok(rm_path, e, 1);
			free(rm_path);
			rm_path = NULL;
			close(fd);
		}
		tmp = tmp->next;
	}
}
