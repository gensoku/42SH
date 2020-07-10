/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history__cmpt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 05:26:21 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/30 05:26:24 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static char			*setup_ret_histo_fail(char *msg, t_env *e, char **path)
{
	display_error(0, msg, e);
	e->last_status = 1;
	if (path)
		ft_memdel((void **)path);
	return (NULL);
}

static char			*setup_ret_histo_match(char *to_ret, char **to_del)
{
	char			*ret;

	ret = ft_strdup(to_ret);
	if (to_del)
		ft_memdel((void **)to_del);
	return (ret);
}

static t_hentries	*set_histo_entries(t_history *t)
{
	t_hentries		*tmp;

	tmp = (t && t->entries) ? t->entries : NULL;
	while (tmp && tmp->id != t->offset)
		tmp = tmp->next;
	return (tmp);
}

char				*built_history__replace(t_history *history, t_env *e)
{
	char			*history_path;
	t_hentries		*tmp;
	int				history_fd;

	if (!history)
		return (setup_ret_histo_fail(HIST_ERR_STRUCT, e, NULL));
	if (!(history_path = built_history__path()))
		return ((setup_ret_histo_fail(NULL, e, NULL)));
	if ((history_fd = open(history_path, (O_RDONLY | O_CREAT),
		get_rights())) == -1)
	{
		return (setup_ret_histo_fail(HIST_ERR_FILE, e, &history_path));
	}
	built_history__read(history, history_fd);
	close(history_fd);
	if (!built_history__parse(history))
		return (setup_ret_histo_fail(HIST_ERR_PARSE, e, &history_path));
	tmp = set_histo_entries(history);
	if (tmp && tmp->cmd)
		return (setup_ret_histo_match(tmp->cmd, &history_path));
	ft_memdel((void **)&history_path);
	return (NULL);
}
