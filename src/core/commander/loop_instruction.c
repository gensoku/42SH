/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 09:18:45 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/22 01:12:51 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void	load_redir_exec(t_env *e, t_token *tmp)
{
	tmp = e->split_tok;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		check_redir_exec(e, tmp);
	if (e->left_redir)
		del_list_redir(e);
	e->left_redir = NULL;
}

static	void	parse_command(char **commands, t_env *e, t_token *tmp)
{
	int			i;

	i = 0;
	while (commands[i])
	{
		parser_token(commands[i], e, 0);
		tmp = e->split_tok;
		while (tmp)
		{
			check_replace_back_quote(&tmp->first, e);
			check_replace_back_quote(&tmp->second, e);
			tmp = tmp->next;
		}
		if (!e->split_tok)
		{
			ft_putendl_fd(E_ERR ? E_ERR : "error on parsing", 2);
			break ;
		}
		else
			load_redir_exec(e, tmp);
		e->split_tok ? del_all_tokens(e->split_tok) : 0;
		e->split_tok = NULL;
		i++;
	}
}

void			destroy_and_print(char ***arr, t_env *e, char **tmp, int o)
{
	if (arr && *arr)
		ft_del_tab(*arr);
	if (tmp)
		ft_memdel((void **)tmp);
	if (o && e->errno_du_pauvre)
		ft_putendl_fd(e->errno_du_pauvre, 2);
	else if (o)
		ft_putendl_fd("Error on parsing arg is probably empty", 2);
}

void			instruction(char *line, int sub_flag, t_env *e)
{
	char		**array;
	char		*tmp;

	if (!line)
		return ;
	tmp = ft_strdup(line);
	loc_var_rep(e, &tmp, 0, 0);
	array = strsplit_command(tmp, e);
	e->sub_shell = sub_flag;
	if (e->errno_du_pauvre)
	{
		destroy_and_print(&array, e, &tmp, 1);
		return ;
	}
	(e->errno_du_pauvre) ? ft_memdel((void **)&e->errno_du_pauvre) : 0;
	e ? e->split_tok = NULL : 0;
	if (!array)
	{
		destroy_and_print(&array, e, &tmp, 1);
		return ;
	}
	parse_command(array, e, NULL);
	ft_del_tab(array);
	array = NULL;
	(tmp) ? ft_memdel((void **)&tmp) : 0;
}
