/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 00:26:35 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/27 00:26:37 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

int					is_a_valid_tok(char *line)
{
	int				len;

	len = ft_strlen(line);
	if (!line || !len)
		return (0);
	if (len > 0 && !ft_strcmp(&line[len - 1], "|") && (len == 1 ||
		check_back_from(line, len - 2) % 2 == 0))
		return (1);
	if (len > 1 && !ft_strcmp(&line[len - 2], "||") && (len == 2 ||
		check_back_from(line, len - 3) % 2 == 0))
		return (1);
	if (len > 0 && !ft_strcmp(&line[len - 1], "&") && (len == 1 ||
		check_back_from(line, len - 2) % 2 == 0))
		return (1);
	if (len > 1 && !ft_strcmp(&line[len - 2], "&&") && (len == 2 ||
		check_back_from(line, len - 3) % 2 == 0))
		return (1);
	if (len > 0 && !ft_strcmp(&line[len - 1], ";") && (len == 1 ||
		check_back_from(line, len - 2) % 2 == 0))
		return (1);
	if (len > 1 && !ft_strcmp(&line[len - 2], ">|") && (len == 2 ||
		check_back_from(line, len - 3) % 2 == 0))
		return (1);
	return (0);
}

int					get_type_search(char *line)
{
	char			**tab_args;
	int				i;

	if (!line)
		return (0);
	tab_args = ft_strsplit_spec(line, 1);
	if (!tab_args)
		return (0);
	i = 0;
	while (tab_args[i])
		i++;
	if (i == 1 || is_a_valid_tok(tab_args[i - 2]))
	{
		ft_del_tab(tab_args);
		return (1);
	}
	ft_del_tab(tab_args);
	return (2);
}

char				*get_last_arg(char *line)
{
	char			**tab_args;
	char			*ret;
	int				i;

	tab_args = ft_strsplit_spec(line, 1);
	i = 0;
	ret = NULL;
	if (tab_args)
	{
		while (tab_args[i])
			i++;
		ret = ft_strdup(tab_args[i - 1]);
	}
	ft_del_tab(tab_args);
	return (ret);
}

char				*get_line_qu_hdoc(t_env *e)
{
	char			*ret;

	ret = NULL;
	if (e->save_quote)
	{
		ret = ft_strnew(ft_strlen(e->save_quote) + ft_strlen(e->line) + 1);
		ft_strcat(ret, e->save_quote);
		e->line ? ft_strcat(ret, e->line) : 0;
	}
	else if (e->heredoc.end_file_confirm)
	{
		ret = ft_strnew(ft_strlen(e->heredoc.end_file_confirm) +
			ft_strlen(e->line) + 1);
		ft_strcat(ret, e->heredoc.end_file_confirm);
		e->line ? ft_strcat(ret, e->line) : 0;
	}
	else
		ret = (e->line) ? ft_strdup(e->line) : NULL;
	return (ret);
}
