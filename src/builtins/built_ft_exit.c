/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ft_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:41:56 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 06:52:57 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void			check_exit(char **tab1, t_env *e)
{
	if (tab1[1] && !tab1[2])
		ft_exit(ft_atoi(tab1[1]), e, 0);
	else if (tab1[1] && tab1[2])
	{
		e->last_status = 1;
		ft_putendl_fd("error exit too many arguments", 2);
	}
	else
		ft_exit(0, e, 0);
	return ;
}

static	void	norm_exit(t_env *e, int opt)
{
	if (!opt && !e->interactive)
	{
		ft_putstr(RED);
		ft_putendl("Bye");
		ft_putstr(RESET);
	}
	(e->env) ? ft_del_tab(e->env) : (void)opt;
	(e->current) ? ft_memdel((void **)&(e->current)) : (void)opt;
	(e->home) ? ft_memdel((void **)&(e->home)) : (void)opt;
	(e->prev_histo) ? ft_memdel((void **)&(e->prev_histo)) : (void)opt;
	(e->saved_histo) ? ft_memdel((void **)&(e->saved_histo)) : (void)opt;
	(e->line) ? ft_memdel((void **)&(e->line)) : (void)opt;
	(e->cut) ? ft_memdel((void **)&(e->cut)) : (void)opt;
	(e->save_quote) ? ft_memdel((void **)&(e->save_quote)) : (void)opt;
	(e->comp_current) ? ft_memdel((void **)&(e->comp_current)) : (void)opt;
	(e->ret_comp) ? ft_memdel((void **)&(e->ret_comp)) : (void)opt;
	ft_memdel((void**)&(e->heredoc.end_file_confirm));
	ft_memdel((void**)&(e->heredoc.end_file));
	(e->histo) ? del_t_histo(e->histo) : (void)opt;
	(e->left_redir) ? del_list_redir(e) : (void)opt;
	(e->errno_du_pauvre) ? ft_memdel((void**)&(e->errno_du_pauvre)) : (void)opt;
	(e->agreg_tmp) ? ft_memdel((void**)&(e->agreg_tmp)) : (void)opt;
	(e->tmp_env) ? del_tmp_env(e) : (void)opt;
	d_all_var(e->all_var);
	e->all_var = NULL;
}

void			ft_exit(int n, t_env *e, int opt)
{
	norm_exit(e, opt);
	(e->paths) ? del_t_spath(e->paths) : (void)opt;
	ft_memdel((void **)&e->cur_direc);
	(e->alternate_paths) ? del_t_spath(e->alternate_paths) : (void)opt;
	e->alternate_paths = NULL;
	e->paths = NULL;
	del_t_comp(e->comp_path);
	e->comp_exe = NULL;
	e->comp_path = NULL;
	(e->cursor) ? ft_memdel((void **)&e->cursor) : (void)opt;
	(e->childs) ? del_t_childs(e->childs) : (void)opt;
	e->childs = NULL;
	(e->count_qu) ? ft_memdel((void **)&e->count_qu) : (void)opt;
	del_list_av(e);
	del_all_tokens(e->split_tok);
	e->split_tok = NULL;
	del_list_redir(e);
	(e->hash) ? ft_memdel((void**)e->hash) : 0;
	e->interactive ? tcsetattr(0, TCSANOW, &e->oterm) : 0;
	free(e);
	e = NULL;
	exit(n);
}
