/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_build_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 09:12:53 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:05:46 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	int			check_sub_error_last(t_env *e, t_parser *tf)
{
	int				flemme;

	if (tf->tok && tf->tok[0] == '(' && (tf->arg1 != NULL || tf->arg2 != NULL))
		return (1);
	flemme = (e->split_tok && e->split_tok->type) ? e->split_tok->type : 0;
	if (e->split_tok && (flemme == R_REDIR || flemme == R_D_REDIR ||
		flemme == L_REDIR || flemme == L_D_REDIR) && !e->split_tok->second)
		return (1);
	return (0);
}

static	void		last_token(t_env *e, t_parser *tf, int agreg)
{
	char *trimed;

	if (tf->flag == 1 && agreg == 0)
	{
		del_all_tokens(e->split_tok);
		e->split_tok = NULL;
		del_parser_tf(tf);
		(!e->errno_du_pauvre) ? e->errno_du_pauvre = ft_strdup(E_SY) : 0;
	}
	else
	{
		if (check_sub_error_last(e, tf))
		{
			del_all_tokens(e->split_tok);
			e->split_tok = NULL;
			del_parser_tf(tf);
			!e->errno_du_pauvre ? e->errno_du_pauvre = ft_strdup(E_SB) : 0;
			return ;
		}
		trimed = ft_strtrim(tf->tok);
		push_front_token(trimed, tf, e);
		free(trimed);
		trimed = NULL;
		del_parser_tf(tf);
	}
}

static	void		norm_set_tf_flag(char *line, t_parser *tf, int opt)
{
	if (opt)
	{
		del_all_tokens(CTX(split_tok));
		CTX(split_tok) = NULL;
		del_parser_tf(tf);
		return ;
	}
	if (tf->back_flag == 0 && line[tf->i] == '\\')
		tf->back_flag = 1;
	else if (tf->back_flag == 1)
		tf->back_flag = 2;
	else if (tf->back_flag == 2)
		tf->back_flag = (line[tf->i] == '\\') ? 1 : 0;
}

static	int			norm_1_ligne_(t_parser *tf, int opt, char *line)
{
	int tmp;

	if (opt)
	{
		set_sep_flags(line, tf->i, &(CTX(flag)), CTX(count_qu));
		norm_set_tf_flag(line, tf, 0);
		return (1337);
	}
	tmp = tf->agreg_int;
	tf->agreg_int = 0;
	return (tmp);
}

void				parser_token(char *line, t_env *e, int agreg)
{
	t_parser	*tf;

	tf = get_helper_tf();
	e->flag = 0;
	while (line[tf->i])
	{
		norm_1_ligne_(tf, 1, line);
		if ((tf->ret = ft_istoken(line, tf->i, tf, e)) > 0)
		{
			if (loop_create_token(line, e, tf, agreg) == -1)
			{
				norm_set_tf_flag(NULL, tf, 1);
				return ;
			}
			agreg = norm_1_ligne_(tf, 0, NULL);
		}
		else if (e->errno_du_pauvre)
		{
			tf->flag = 1;
			break ;
		}
		else
			loop_args_token(tf, line);
	}
	last_token(e, tf, agreg);
}
