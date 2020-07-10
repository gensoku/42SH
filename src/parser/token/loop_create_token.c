/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_create_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 00:17:56 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:05:04 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	char	*get_token(char *line, int ret, t_env *e)
{
	char		*token;
	int			i;

	if ((token = (char*)malloc(sizeof(char) * ret + 1)) == NULL)
		display_error(-1, "malloc failed char *", e);
	i = 0;
	ft_bzero(token, ret + 1);
	while (ret > 0)
	{
		token[i] = line[i];
		i++;
		ret--;
	}
	token[i] = 0;
	return (token);
}

static	int		pars_2(t_parser *tf, int agreg, t_env *e)
{
	if ((!tf->arg1 && agreg == 0) && ft_strcmp(tf->tok, "|") == 0)
	{
		E_ERR = ft_strdup("syntax error near unexpected token `|'");
		return (-1);
	}
	if ((!tf->arg1 && agreg == 0) && ft_strcmp(tf->tok, "||") == 0)
	{
		E_ERR = ft_strdup("syntax error near unexpected token `||'");
		return (-1);
	}
	if ((!tf->arg1 && agreg == 0) && ft_strcmp(tf->tok, "&&") == 0)
	{
		E_ERR = ft_strdup("syntax error near unexpected token `&'");
		return (-1);
	}
	if ((!tf->arg1 && agreg == 0) && ft_strcmp(tf->tok, "&") == 0)
	{
		E_ERR = ft_strdup("syntax error near unexpected token `&'");
		return (-1);
	}
	tf->i += tf->ret;
	tf->flag = 1;
	return (0);
}

static	int		bg_tok_exept(t_parser *tf, t_env *e)
{
	if ((ft_strcmp(tf->tok, "&") == 0 && !tf->arg2) ||
		(tf->tok && tf->tok[0] == '(' && (tf->arg1 || tf->arg2)))
	{
		del_all_tokens(e->split_tok);
		e->split_tok = NULL;
		E_ERR = (tf->type == SUB_RED && !E_ERR) ?
			ft_strdup(E_SB) : ft_strdup(E_BG);
		return (-1);
	}
	return (0);
}

static	int		del_tok_return(t_env *e)
{
	del_all_tokens(e->split_tok);
	e->split_tok = NULL;
	return (-1);
}

int				loop_create_token(char *line, t_env *e, t_parser *tf, int agreg)
{
	char *trimed;

	if (tf->flag == 1 && tf->agreg_int == 0 && agreg == 0)
		return (del_tok_return(e));
	if (tf->tok)
	{
		if (bg_tok_exept(tf, e))
			return (-1);
		trimed = ft_strtrim(tf->tok);
		push_front_token(trimed, tf, e);
		ft_memdel((void**)&trimed);
		ft_memdel((void**)&tf->tok);
		(tf->arg1) ? ft_memdel((void**)&tf->arg1) : (void)tf->arg1;
		tf->arg1 = tf->arg2 ? ft_strdup(tf->arg2) : NULL;
		(tf->arg2) ? ft_memdel((void**)&tf->arg2) : (void)tf->arg2;
	}
	if ((tf->tok = get_token(&line[tf->i], tf->ret, e)) == NULL)
		return (del_tok_return(e));
	return (pars_2(tf, agreg, e));
}
