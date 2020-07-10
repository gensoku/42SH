/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history__catch.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:47:22 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 04:46:50 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		built_history__catch_entry(int history_fd, char *cmd)
{
	static t_foldm		entry[] = {
		{ "time", NULL },
		{ "cmd", NULL },
		{ NULL, NULL }
	};
	struct timeval		tp;
	char				*append;
	char				*time;

	gettimeofday(&tp, NULL);
	time = ft_itoa(tp.tv_sec);
	ft_foldassign(entry, "time", (void *)time);
	ft_foldassign(entry, "cmd", (void *)cmd);
	append = ft_fold(": {time}:0;{cmd}\n", entry);
	write(history_fd, append, ft_strlen(append));
	ft_memdel((void **)&time);
	ft_memdel((void **)&append);
	return ;
}

void			built_history__catch(char *cmd)
{
	int		history_fd;
	char	*p_cmd;
	char	*path;

	if (!cmd || !*cmd)
		return ;
	p_cmd = cmd;
	path = NULL;
	path = built_history__path();
	if ((history_fd = open(path,
		(O_WRONLY | O_CREAT | O_APPEND), get_rights())) == -1)
	{
		ft_memdel((void **)&path);
		return ;
	}
	built_history__catch_entry(history_fd, p_cmd);
	if (p_cmd != cmd)
		ft_memdel((void **)&p_cmd);
	close(history_fd);
	ft_memdel((void **)&path);
}
