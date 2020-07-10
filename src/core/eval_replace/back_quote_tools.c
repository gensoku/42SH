/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_quote_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 06:16:08 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/19 06:16:09 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		call_to_wait(t_token *node_tmp, t_env *e, int opts, char *tmp2)
{
	if (!opts)
	{
		run_tok_right(node_tmp);
		root_tok(node_tmp, e);
		wait_pgid(e->tmp_pgid, e, 1);
		resume_state(e, 0, NULL);
	}
	else
	{
		set_var_("intern_sys_call=true", LOC_VAR, VAR_NEUTRAL);
		exec_tok(tmp2, e, 1);
		remove_var("intern_sys_call");
		if (e->childs && e->childs->child)
		{
			wait_pgid(e->childs->child, e, 1);
			resume_state(e, 0, NULL);
		}
	}
}

static void		del_tmp_node(t_token *node)
{
	if (node)
	{
		ft_memdel((void **)&node->tok);
		ft_memdel((void **)&node->first);
		ft_memdel((void **)&node->second);
	}
}

static void		setup_tmp_call(char **line, int *i, int *k, t_env *e)
{
	t_token		node_tmp;
	char		*tmp2;
	char		*tmp;

	ft_bzero(&node_tmp, sizeof(t_token));
	node_tmp.first = ft_strsub(*line, *i + 1, *k - *i - 1);
	node_tmp.tok = ft_strdup(">");
	node_tmp.second = ft_strdup(TEMPO_BQ);
	node_tmp.type = R_REDIR;
	node_tmp.foreground = 1;
	call_to_wait(&node_tmp, e, 0, NULL);
	tmp = ft_get_file(TEMPO_BQ, node_tmp.fd);
	close(node_tmp.fd);
	tmp ? tmp2 = ft_str_sub_append(*line, tmp, *i, *k - *i + 1) : 0;
	tmp ? *i += ft_strlen(tmp) : 0;
	tmp ? free(*line) : 0;
	*line = ft_strdup(tmp2);
	*line = ft_convert_space(*line, 0, 0, 0);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&tmp2);
	tmp2 = ft_strjoin("rm ", node_tmp.second);
	call_to_wait(&node_tmp, e, 1, tmp2);
	ft_memdel((void **)&tmp2);
	del_tmp_node(&node_tmp);
}

void			bq_check_setup(char **line, int *i, int *k, char **str)
{
	setup_tmp_call(line, i, k, CONTEXT);
	*str = *line;
}
