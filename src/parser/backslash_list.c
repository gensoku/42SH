/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 05:06:00 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static char			*cut_bs(char *str, int cut, int i, int j)
{
	char			*ret;

	ret = NULL;
	if ((ret = (char *)malloc(sizeof(char) * ft_strlen(str))) == NULL)
		display_error(-1, "Malloc failed char *, exit", CONTEXT);
	while (str[i])
	{
		if (cut == i)
			str[i] = str[i];
		else
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = 0;
	return (ret);
}

static	void		cut_norm_1(t_pars_cut *t, t_comp *tmp, int opt)
{
	ft_memdel((void **)&t->tmp_str);
	t->tmp_str = ft_strdup(tmp->name);
	ft_memdel((void**)&(tmp->name));
	tmp->name = cut_bs(t->tmp_str, t->i, 0, 0);
	if (opt)
		t->i--;
}

static	void		norm_remove(t_pars_cut *t, t_comp *tmp, int opt)
{
	if (opt == 0)
	{
		t->flag_on = 1;
		t->tok = tmp->name[t->i];
		cut_norm_1(t, tmp, 1);
	}
	else if (opt == 1)
	{
		t->flag_on = 0;
		t->tok = 0;
		cut_norm_1(t, tmp, 1);
	}
	else if (opt == 2)
		cut_norm_1(t, tmp, 0);
	else if (opt == 3)
	{
		t->flag_on = 0;
		t->tok = 0;
		cut_norm_1(t, tmp, 1);
	}
	else if (opt == 4)
		cut_norm_1(t, tmp, 0);
}

static void			remove_bs(t_comp *tmp)
{
	t_pars_cut		*t;

	t = get_helper_cut();
	t->tmp_str = ft_strdup(tmp->name);
	checks_tild(t->tmp_str, CONTEXT, &tmp->name);
	while (t->i >= 0 && tmp->name[t->i])
	{
		if (t->flag_on == 0 && (tmp->name[t->i] == '\'' ||
				tmp->name[t->i] == '\"') && (t->i == 0 ||
					check_back_from(tmp->name, t->i - 1) == 0))
			norm_remove(t, tmp, 0);
		else if (t->flag_on == 1 && t->tok == '\'' && tmp->name[t->i] == '\'')
			norm_remove(t, tmp, 1);
		else if (t->flag_on == 1 && t->tok == '\"' && tmp->name[t->i] == '\\')
			norm_remove(t, tmp, 2);
		else if (t->flag_on == 1 && t->tok == '\"' && tmp->name[t->i] == '\"')
			norm_remove(t, tmp, 3);
		else if (tmp->name[t->i] == '\\' && t->flag_on == 0)
			norm_remove(t, tmp, 4);
		t->i++;
	}
	ft_memdel((void**)&(t->tmp_str));
	del_t_pars_cut(t);
}

t_comp				*backslash_lst(t_comp *lst)
{
	t_comp			*tmp;
	t_comp			*head;

	if (!lst)
		return (NULL);
	tmp = lst;
	head = lst;
	while (tmp)
	{
		if (!tmp->name)
		{
			tmp = tmp->next;
			continue ;
		}
		remove_bs(tmp);
		tmp = tmp->next;
	}
	return (head);
}
