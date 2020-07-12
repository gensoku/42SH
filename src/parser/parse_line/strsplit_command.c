/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 05:48:46 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/24 07:01:10 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	t_comp	*norm_get_list(t_tools *t, char *str, t_comp *list_elem)
{
	str[t->i] = 0;
	list_elem = push_back_elem_(&str[t->k], list_elem, TOK_WORD);
	str[t->i] = ';';
	t->k = t->i + 1;
	return (list_elem);
}

static	int		get_error_separator(char *str, t_tools *t)
{
	if (t->flag_on == 0 && str[t->i] == ';' && str[t->i + 1] &&
		str[t->i + 1] == ';' && (t->i == 0 || CHECK_SL(str, t->i - 1) == 0))
		return (1);
	return (0);
}

static	int		chk_comand(char *str, t_tools *t, int flag, t_quote *count)
{
	if (str[t->i] == ';' && !flag && !count->pr && !count->bq &&
		(t->i == 0 || check_back_from(str, t->i - 1) % 2 == 0))
		return (1);
	return (0);
}

static	t_comp	*get_list_command(char *str, t_env *e)
{
	t_comp	*list_elem;
	t_quote	ct;
	int		flag;
	t_tools *t;

	list_elem = NULL;
	ft_bzero(&ct, sizeof(t_quote));
	flag = 0;
	t = get_helper_tools_();
	(void)e;
	while (str[t->i])
	{
		if (get_error_separator(str, t))
			return (norm_get_err(str, list_elem, t, 0));
		if (!set_sep_flags(str, t->i, &flag, &ct) &&
			chk_comand(str, t, flag, &ct))
			list_elem = norm_get_list(t, str, list_elem);
		t->i++;
	}
	if (t->i > 0 && (str[t->i - 1] != ';' || (t->i > 1 &&
			CHECK_SL(str, t->i - 1) != 0)))
		list_elem = push_back_elem_(&str[t->k], list_elem, TOK_WORD);
	del_t_tools_(t);
	return (list_elem);
}

char			**strsplit_command(char *str, t_env *e)
{
	t_comp		*list_elem;
	char		**new;

	if (!str)
		return (NULL);
	built_history__catch(str);
	if (str[0] && str[0] == ';')
	{
		list_elem = norm_get_err(str, NULL, NULL, 1);
		return (NULL);
	}
	list_elem = get_list_command(str, e);
	if (!list_elem)
		return (NULL);
	if ((new = (char **)ft_memalloc(sizeof(char *) *
			size_list_t_comp(list_elem) + 1)) == NULL)
		display_error(-1, "Malloc failed char *, exit", get_e(NULL));
	new = t_comp_to_tab(new, list_elem);
	list_elem = NULL;
	return (new);
}
