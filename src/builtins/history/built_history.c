/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:46:57 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/22 01:12:40 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

char			*built_history__path(void)
{
	char		*home_path;
	char		*hist_path;
	size_t		len;

	if (!(home_path = get_env("HOME", CTX(env), 1)))
		return (NULL);
	len = ft_strlen((CTX(hshell)) ? HISTORY_FILENAME_ZSH : HISTORY_FILENAME);
	hist_path = ft_strnew(ft_strlen(home_path) + len + 1);
	ft_strcat(hist_path, home_path);
	ft_strcat(hist_path, "/");
	ft_strcat(hist_path, (CTX(hshell)) ?
		HISTORY_FILENAME_ZSH : HISTORY_FILENAME);
	ft_memdel((void **)&home_path);
	return (hist_path);
}

static int		built_history__options_offset(char *arg, t_history *history)
{
	char		*tmp;
	char		*offset;
	const char	signs[2] = "+-";

	if (!*arg)
		return (1);
	offset = NULL;
	tmp = arg;
	if (ft_strchr(signs, *tmp))
		tmp++;
	if (!*tmp || ft_strchr(signs, *tmp))
		return (0);
	while (ft_isdigit(*tmp) && (offset = tmp))
		tmp++;
	if (arg == tmp || offset == NULL || *tmp)
		return (0);
	else
	{
		offset = ft_strnew(tmp - arg);
		ft_strncpy(offset, arg, tmp - arg);
		history->offset = ft_atoi(offset);
		history->type = HISTORY_OFFSET;
		ft_memdel((void **)&offset);
		return (1);
	}
}

static int		built_history__options_permu(char *arg, t_history *history)
{
	if (!*arg)
		return (1);
	if (ft_strnstr(arg, "-p", 2))
	{
		arg += 2;
		if (*arg)
			return (0);
		history->type = HISTORY_PERMUTE;
		CTX(hshell) = !CTX(hshell);
		return (1);
	}
	return (0);
}

static t_herror	built_history__options(char **arg, t_history *history)
{
	char		*current_arg;
	int			index;

	index = 1;
	while (*arg)
	{
		current_arg = *arg;
		if (built_history__options_permu(current_arg, history))
			return (1);
		if (!built_history__options_offset(current_arg, history))
			return (HISTORY_NOT_FOUND);
		arg++;
		index++;
	}
	return (1);
}

void			built_history(char **arg, t_env *e)
{
	t_history			*history;

	if (!*arg)
		return ;
	arg++;
	history = (t_history *)malloc(sizeof(t_history));
	history->type = HISTORY_ALL;
	history->offset = 0;
	history->total = 0;
	history->raw = NULL;
	history->entries = NULL;
	if (ft_len_tab(arg) > 1)
		built_history__error(HISTORY_TOO_MANY_ARG);
	else if (built_history__error(built_history__options(arg, history)))
		e->last_status = 1;
	else if (history->type == HISTORY_PERMUTE)
	{
		ft_putstr_fd("History switched ", (CTX(fd[0]) == -1) ? 1 : CTX(fd[0]));
		ft_putendl_fd((CTX(hshell)) ? "ZSH" : "default 42sh",
			(CTX(fd[0]) == -1) ? 1 : CTX(fd[0]));
	}
	else
		built_history__print(history, e);
	del_history(&history);
}
