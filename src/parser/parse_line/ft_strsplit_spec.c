/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_spec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 09:09:28 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/22 05:11:56 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	t_comp		*norm_get_list_2(char *str, t_tools *t, t_comp *list_elem)
{
	str[t->i] = 0;
	list_elem = push_back_elem_(&str[t->k], list_elem, TOK_WORD);
	str[t->i] = ' ';
	t->flag_sp = 0;
	return (list_elem);
}

static	void		get_set_wopt_(char *str, t_tools *t, int opt)
{
	if (opt == 0)
	{
		t->flag_on = 1;
		t->tok = str[t->i];
	}
	else if (opt == 1)
	{
		t->flag_on = 0;
		t->tok = 0;
	}
	else if (opt == 2)
	{
		t->k = t->i;
		t->flag_sp = 1;
	}
}

static	t_comp		*get_elem_list(char *str)
{
	t_comp			*list_elem;
	t_tools			*t;

	list_elem = NULL;
	t = get_helper_tools_();
	while (str[t->i])
	{
		if (t->flag_on == 0 && (str[t->i] == '\'' ||
			str[t->i] == '\"') && (t->i == 0 || CHECK_SL(str, t->i - 1) == 0))
			get_set_wopt_(str, t, 0);
		else if (t->flag_on == 1 && t->tok == str[t->i] && (str[t->i] != '\"' ||
		CHECK_SL(str, t->i - 1) == 0))
			get_set_wopt_(str, t, 1);
		if (str[t->i] != ' ' && t->flag_sp == 0)
			get_set_wopt_(str, t, 2);
		else if (str[t->i] == ' ' && t->flag_sp == 1 && t->flag_on == 0 &&
			check_back_from(str, t->i - 1) % 2 == 0)
			list_elem = norm_get_list_2(str, t, list_elem);
		t->i++;
	}
	if (t->flag_sp == 1)
		list_elem = push_back_elem_(&str[t->k], list_elem, TOK_WORD);
	del_t_tools_(t);
	return (list_elem);
}

static int			chk_var(char *name)
{
	if (!name)
		return (0);
	if (ft_strchr(name, '='))
		return (1);
	return (0);
}

char				**ft_strsplit_spec(char *str, int opt)
{
	t_comp			*list_elem;
	char			**new;
	char			*trimed;

	if (!str)
		return (NULL);
	trimed = NULL;
	list_elem = get_elem_list(str);
	if (list_elem)
	{
		if (list_elem->name)
			trimed = ft_strtrim(list_elem->name);
		if (trimed && ft_strcmp(trimed, "echo") != 0 &&
			ft_strcmp(trimed, "env") != 0 && !chk_var(list_elem->name) && !opt)
			list_elem = backslash_lst(list_elem);
		if (trimed)
			ft_memdel((void**)&trimed);
	}
	if (!list_elem)
		return (NULL);
	if ((new = (char**)ft_memalloc(sizeof(char *)
			* size_list_t_comp(list_elem) + 1)) == NULL)
		display_error(-1, "Malloc failed char *, exit", CONTEXT);
	new = t_comp_to_tab(new, list_elem);
	return (new);
}
