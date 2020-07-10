/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history__print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:49:51 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 04:44:48 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		built_history__print_entries(t_history *history)
{
	t_hentries		*entries;
	long long int	offset;

	offset = -1;
	entries = history->entries;
	if (history->type == HISTORY_OFFSET && history->offset < 0)
	{
		offset = history->total - ABS(history->offset);
		if (offset <= 0)
			offset = 1;
	}
	while (entries)
	{
		ft_putnbr_fd(entries->id, (CTX(fd[0]) == -1) ? 1 : CTX(fd[0]));
		ft_putstr_fd("  ", (CTX(fd[0]) == -1) ? 1 : CTX(fd[0]));
		ft_putendl_fd(entries->cmd, (CTX(fd[0]) == -1) ? 1 : CTX(fd[0]));
		if (offset && offset == entries->id)
			break ;
		entries = entries->next;
	}
	return ;
}

static int		setup_ret_histo_fail(char *msg, t_env *e, char **path)
{
	display_error(0, msg, e);
	e->last_status = 1;
	if (path)
		ft_memdel((void **)path);
	return (0);
}

int				built_history__print(t_history *history, t_env *e)
{
	char		*history_path;
	int			history_fd;

	if (!history)
		return (setup_ret_histo_fail(HIST_ERR_STRUCT, e, NULL));
	if (!(history_path = built_history__path()))
	{
		e->last_status = 1;
		return (0);
	}
	if ((history_fd = open(history_path, (O_RDONLY | O_CREAT),
		get_rights())) == -1)
	{
		return (setup_ret_histo_fail(HIST_ERR_FILE, e, &history_path));
	}
	built_history__read(history, history_fd);
	close(history_fd);
	if (!built_history__parse(history))
		return (setup_ret_histo_fail(HIST_ERR_PARSE, e, &history_path));
	built_history__print_entries(history);
	ft_memdel((void **)&history_path);
	return (1);
}
