/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:49:06 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	aac_p1(t_env *e, char *save)
{
	int type;

	move_home(e);
	tputs(tgetstr("cr", NULL), 1, spec_put);
	tputs(tgetstr("cd", NULL), 1, spec_put);
	display_error(0, ERR_ST, e);
	tputs(tgetstr("cr", NULL), 1, spec_put);
	if (e->line)
		free(e->line);
	e->line = ft_strdup(save);
	cursor_set(e, e->cursor, e->line);
	if ((type = check_quote(e)) > 0)
		print_prompt_quote(type);
	else
		print_curseur(NULL);
	print_with_end_space(e);
}

void	aac_p2(t_env *e)
{
	tputs(tgetstr("cd", NULL), 1, spec_put);
	print_comp2(e, e->ret_comp);
	if (e->ret_comp)
		free(e->ret_comp);
	e->ret_comp = NULL;
}

void	aac_p3(t_env *e, char *save)
{
	int type;

	if (e->line)
		free(e->line);
	e->line = ft_strdup(save);
	move_home(e);
	tputs(tgetstr("cr", NULL), 1, spec_put);
	tputs(tgetstr("cd", NULL), 1, spec_put);
	if ((type = check_quote(e)) > 0)
		print_prompt_quote(type);
	else
		print_curseur(NULL);
	cursor_set(e, e->cursor, e->line);
	print_with_end_space(e);
}
