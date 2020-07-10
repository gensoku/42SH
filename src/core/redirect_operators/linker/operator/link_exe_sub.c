/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_exe_sub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 08:27:33 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/19 08:27:34 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static char		*sub_formated(t_token *node, char *formated, t_env *e)
{
	char		*quote;
	size_t		len;

	len = ft_strlen(node->tok);
	formated = ft_strsub(node->tok, 1, len > 2 ? len - 2 : 0);
	quote = add_backslash(formated, 0, 0);
	ft_memdel((void **)&formated);
	formated = ft_strdup(quote);
	ft_memdel((void **)&quote);
	quote = ft_strjoin(e->heredoc_null ? "21sh -SH  " : "21sh -S ", formated);
	formated ? free(formated) : 0;
	formated = ft_strjoin(quote, "\"");
	ft_memdel((void **)&quote);
	return (formated);
}

void			sub_setup(t_token *unused, t_env *e, int *flag_stop,
	t_token *node)
{
	char		*formated;

	(*flag_stop != 1) ? e->last_status = -1 : 0;
	(void)unused;
	formated = NULL;
	formated = sub_formated(node, formated, e);
	if (node->previous && node->previous->type == P_REDIR)
	{
		run_pipe(node->previous, formated, e);
		formated ? ft_memdel((void **)&formated) : 0;
		return ;
	}
	exec_tok(formated, e, 1);
	ft_memdel((void **)&formated);
	if (node->previous)
	{
		root_tok(node->previous, e);
		return ;
	}
}
