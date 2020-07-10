/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_unfinished_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:04:45 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		mini_norm(int type, t_env *e)
{
	if ((type = check_quote(e)) > 0)
		unfinished_line(e, type);
	else
		append_load_ins(e, type);
}

void			send_instruction(t_env *e)
{
	ft_putchar('\n');
	if (!e->heredoc.end_file_tog)
		mini_norm(0, e);
	else
		heredoc_prompt();
	(e->saved_histo) ? ft_memdel((void**)&(e->saved_histo)) : 0;
	del_tmp_env(e);
}

static	char	*norm_instru_free_join(char *tmp, t_env *e)
{
	free(E_SQ);
	if (E_F & FLAG_DQU && tmp && ft_strlen(tmp) > 0
		&& check_back_from(tmp, ft_strlen(tmp) - 1) % 2 != 0)
	{
		tmp[ft_strlen(tmp) - 1] = '\0';
		E_SQ = ft_strdup(tmp);
	}
	else
		E_SQ = ft_strjoin(tmp, "\n");
	free(tmp);
	tmp = ft_strdup(E_SQ);
	free(E_SQ);
	return (tmp);
}

void			unfinished_line(t_env *e, int type)
{
	char		*tmp;

	if (E_SQ)
	{
		tmp = ft_strjoin(E_SQ, E_LI);
		if (!(E_F & FLAG_BACK) && ((!(E_F & FLAG_DQU)) || (ft_strlen(E_SQ)
			> 0 && check_back_from(E_SQ, ft_strlen(E_SQ) - 1) % 2 == 0)))
			tmp = norm_instru_free_join(tmp, e);
		else
			free(E_SQ);
		E_SQ = ft_strdup(tmp);
		ft_memdel((void**)&tmp);
	}
	else
	{
		if (!(E_F & FLAG_BACK) && ((!(E_F & FLAG_DQU)) || (ft_strlen(E_LI)
				> 0 && check_back_from(E_LI, ft_strlen(E_LI) - 1) % 2 == 0)))
			E_SQ = ft_strjoin(E_LI, "\n");
		else
			E_SQ = ft_strdup(E_LI);
	}
	print_prompt_quote(type);
}
