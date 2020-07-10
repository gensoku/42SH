/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check_for_set.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 10:51:48 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/03 10:51:50 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	t_loc_var		*check_for_set_get_var(char *cut, char *line)
{
	t_loc_var			*tmp;

	if (cut)
	{
		cut[0] = 0;
		tmp = get_var_ptr(CONTEXT, line, CASE_TRUE);
		cut[0] = '=';
	}
	else
		tmp = get_var_ptr(CONTEXT, line, CASE_TRUE);
	return (tmp);
}

static	void			check_for_set_no_match(char *cut, char *line)
{
	if (cut)
	{
		set_var_(line, ENV_VAR, VAR_X);
		export_to_setenv(line, NULL, NULL);
	}
	else
		set_var_(line, TMP_VAR, VAR_X);
}

static	void			check_read_only(char *cut, t_loc_var *tmp, char *line)
{
	if (cut && tmp->status & VAR_R)
	{
		ft_putstr_fd(SH_NAME, 2);
		ft_putstr_fd(" read-only variable: ", 2);
		builtin_setup_error(tmp->key, CONTEXT, 1);
	}
	else
	{
		tmp->type = ENV_VAR;
		(tmp->value) ? ft_memdel((void **)&tmp->value) : 0;
		if (cut && cut[1])
			tmp->value = ft_strdup(&cut[1]);
		else
			tmp->value = ft_strdup("\'\'");
		export_to_setenv(line, NULL, NULL);
	}
}

void					check_for_set(char *line)
{
	char				*cut;
	t_loc_var			*tmp;

	cut = ft_strchr(line, '=');
	tmp = check_for_set_get_var(cut, line);
	if (!tmp)
		check_for_set_no_match(cut, line);
	else if (tmp->type == TMP_VAR || tmp->type == LOC_VAR)
		check_read_only(cut, tmp, line);
	else if (tmp->type == ENV_VAR && cut)
		check_read_only(cut, tmp, line);
}
