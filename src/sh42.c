/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 10:41:40 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/03 06:01:10 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

void				get_lines(t_env *e, int fd)
{
	e->heredoc_null = 1;
	while (get_next_line(fd, &(e->line)) > 0)
	{
		instruction(e->line, 0, e);
		(e->line) ? ft_memdel((void **)&(e->line)) : 0;
	}
}

static int			set_opt(char *line, int *opt)
{
	int				i;

	if (!line || line[0] != '-')
		return (0);
	i = 1;
	while (line[i])
	{
		if (line[i] == 'H' || line[i] == 'h')
			*opt |= FLAG_H;
		if (line[i] == 'S' || line[i] == 's')
			*opt |= FLAG_S;
		i++;
	}
	if (*opt)
		return (1);
	return (0);
}

static	void		set_termios_env(t_env *e, char **env, int ret)
{
	struct termios	old;
	struct termios	cur;

	ft_bzero(&old, sizeof(struct termios));
	ft_bzero(&cur, sizeof(struct termios));
	if (set_shell_fg() != 0)
	{
		ret = (tcgetattr(0, &old) == -1) ? -1 : 0;
		tcgetattr(0, &cur);
		cur.c_lflag &= ~(ECHO | ISIG | TOSTOP | ICANON);
		cur.c_cc[VMIN] = 1;
		cur.c_cc[VTIME] = 0;
		e->term = cur;
		e->oterm = (ret == 0) ? old : cur;
		ft_set_term(&e->term);
	}
	else
		e->interactive = 0;
	if (!env || !env[0])
		init_env(NULL, e);
	else
		init_env(env, e);
	ft_set_caps(e);
	resize();
}

static	void		args_treatment(char **av, t_env *e, int i)
{
	char			*opt_s;

	e->interactive = 0;
	opt_s = NULL;
	if (set_opt(av[i], &e->opt) && e->opt & FLAG_S)
	{
		(e->opt & FLAG_H) ? e->heredoc_null = 1 : 0;
		opt_s = ft_implode(&av[2], ' ');
		instruction(opt_s, 0, e);
		ft_memdel((void **)&opt_s);
	}
	else
		while (av[i])
		{
			instruction(av[i], 0, e);
			i++;
		}
	ft_exit(e->last_status, e, 1);
}

int					main(int i, char **av, char **env)
{
	t_env			*e;

	if ((e = (t_env*)ft_memalloc(sizeof(t_env))) == NULL)
		display_error(-1, "malloc failed struc sh, exit", NULL);
	get_e(e);
	e->interactive = av[1] ? 0 : 1;
	set_termios_env(e, env, 0);
	i = 1;
	if (av[i])
		args_treatment(av, e, i);
	if (e->interactive)
		print_prompt(e);
	else if (!av[1])
		get_lines(e, 0);
	return (0);
}
