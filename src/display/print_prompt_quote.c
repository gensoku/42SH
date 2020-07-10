/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/16 07:17:15 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static char const *g_tab[] = {
	0,
	")",
	"`",
	"}",
	"quote ",
	"dquote",
	"backslash ",
	"|| or && or |",
	0
};

void		print_prompt_quote(int i)
{
	char	*prompt;

	if (get_var_ptr(CONTEXT, "intern_prompt_var", CASE_TRUE))
	{
		get_size_prompt("");
		return ;
	}
	ft_putstr(CYAN);
	if (i > 0 && i <= 7)
	{
		prompt = ft_strnew(MAX_PROMPT_LEN);
		ft_strcat(prompt, "[expected ");
		ft_strcat(prompt, g_tab[i]);
		ft_strcat(prompt, "]");
		write(1, prompt, ft_strlen(prompt));
		ft_strcat(prompt, ":> ");
		ft_putstr(RESET);
		ft_putstr(BLUE);
		ft_putstr(":> ");
		ft_putstr(RESET);
		get_size_prompt(prompt);
		ft_memdel((void **)&prompt);
	}
}
