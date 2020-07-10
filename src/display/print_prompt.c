/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 10:41:23 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/15 04:59:17 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void				lil_col_tool(char *content, char *color,
	char *to_add, char **dest)
{
	ft_putstr(RESET);
	ft_putstr(color);
	ft_putstr(content);
	ft_putstr(RESET);
	if (to_add && dest)
		ft_strcat(*dest, to_add);
}

void				common_prompt_(char *prompt)
{
	prompt = ft_strnew(MAX_PROMPT_LEN);
	ft_strcat(prompt, CUS_SHELL);
	ft_putstr(GREEN);
	ft_putstr(prompt);
	ft_putstr(RESET);
	ft_strcat(prompt, " >> ");
	ft_putstr(YELLOW);
	ft_putstr(" >> ");
	ft_putstr(RESET);
	get_size_prompt(prompt);
	ft_memdel((void **)&prompt);
}

void				prompt_time(void)
{
	time_t			cur;
	struct tm		*calendar;

	time(&cur);
	calendar = localtime(&cur);
	mktime(calendar);
	ft_putstr(RESET);
	ft_putstr(BLUE);
	ft_putstr(" ");
	(ft_size_int(calendar->tm_hour) == 1) ? ft_putnbr(0) : 0;
	ft_putnbr(calendar->tm_hour);
	ft_putstr(":");
	(ft_size_int(calendar->tm_min) == 1) ? ft_putnbr(0) : 0;
	ft_putnbr(calendar->tm_min);
	ft_putstr("");
	ft_putstr(RESET);
}

void				custom_update_(struct passwd *owner, char *prompt)
{
	char			*hostname;
	char			*tmp;

	if (!owner)
		common_prompt_(prompt);
	else
	{
		prompt = ft_strnew(MAX_PROMPT_LEN);
		ft_strcat(prompt, owner->pw_name);
		hostname = ft_strnew(1024);
		gethostname(hostname, 1024);
		lil_col_tool(prompt, GREEN, NULL, NULL);
		lil_col_tool("@", RED, "@", &prompt);
		lil_col_tool(hostname, CYAN, hostname, &prompt);
		if ((tmp = get_env("SH_TIME", CTX(env), CASE_TRUE)) &&
			!ft_strcmp(tmp, "TRUE"))
		{
			ft_strcat(prompt, " 00:00");
			prompt_time();
		}
		lil_col_tool(" >> ", YELLOW, " >> ", &prompt);
		get_size_prompt(prompt);
		ft_memdel((void **)&tmp);
		ft_memdel((void **)&hostname);
	}
}

void				print_curseur(char *custom)
{
	char			*prompt;
	char			*available;

	if (get_var_ptr(CONTEXT, "intern_prompt_var", CASE_TRUE))
	{
		(custom) ? ft_putstr(custom) : 0;
		get_size_prompt(custom ? custom : "");
		return ;
	}
	prompt = NULL;
	available = get_env("GETPWN", CTX(env), CASE_TRUE);
	if (available && !ft_strcmp(available, "TRUE"))
		custom_update_(getpwuid(getuid()), prompt);
	else
		common_prompt_(prompt);
	ft_memdel((void **)&available);
}
