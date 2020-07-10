/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_double_left_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/16 10:52:26 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void				run_tok_left2(t_env *e, char *path)
{
	int				fd;

	if (!path)
	{
		ft_putendl_fd("erreur on heredoc setup.", 2);
		return ;
	}
	fd = open(path, (O_RDWR | O_CREAT), get_rights());
	if (fd == -1)
	{
		ft_putendl_fd(ERROR_R_FILE, 2);
		return ;
	}
	if (e->heredoc.end_file_confirm)
		ft_putstr_fd(e->heredoc.end_file_confirm, fd);
	close(fd);
}
