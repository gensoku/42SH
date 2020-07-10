/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_redir_tempo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/16 10:52:04 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	check_close_fd_redir(t_token *lst, t_env *e)
{
	t_token		*tmp;
	char		*tmp2;

	tmp = lst;
	tmp2 = NULL;
	while (tmp)
	{
		if (check_type_redir(tmp) == 1)
		{
			if (tmp->fd > 2)
				close(tmp->fd);
			if (tmp->second && ft_strncmp(tmp->second, TEMPO,
					ft_strlen(TEMPO)) == 0)
			{
				tmp2 = ft_strjoin("rm ", tmp->second);
				exec_tok(tmp2, e, 1);
				wait_pgid(e->childs->child, e, 1);
				resume_state(e, 0, NULL);
				free(tmp2);
				tmp2 = NULL;
			}
		}
		tmp = tmp->previous;
	}
}
