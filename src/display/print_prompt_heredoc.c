/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 07:17:49 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:59:19 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void	heredoc_prompt(void)
{
	char	*prompt;

	if (get_var_ptr(CONTEXT, "intern_prompt_var", CASE_TRUE))
	{
		get_size_prompt("");
		return ;
	}
	prompt = ft_strdup("[stdin redirect       <<] > ");
	ft_putstr(YELLOW);
	write(1, "[stdin redirect       <<]", 25);
	ft_putstr(RESET);
	ft_putstr(GREEN);
	ft_putstr(" > ");
	ft_putstr(RESET);
	get_size_prompt(prompt);
	ft_memdel((void **)&prompt);
}
