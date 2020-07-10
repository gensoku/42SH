/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_read_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:49:33 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/23 09:49:37 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static int			loop_r_read_treat(char buf[MAX_LEN + 4],
	t_read *r, int i, uint64_t y)
{
	unsigned char	*s;
	int				ret;

	ret = 0;
	if (buf[0] != 27 && buf[0] != 4)
	{
		while (buf[i++])
		{
			if ((mo_r_display((int)buf[i], r)))
				return (1);
		}
	}
	else
	{
		i = 0;
		s = (unsigned char*)buf;
		while (i < 8)
		{
			y += (s[i] << (8 * i));
			i++;
		}
		if ((mo_r_display(y, r)))
			return (1);
	}
	return (ret);
}

static int			setup_read_read_display(t_env *e, t_read *r)
{
	char			*tmp;

	tmp = NULL;
	e->color_def = 0;
	ft_putstr(RESET);
	r_move_ctrl_c(e);
	(is_opt_set(r->opts, 's')) ?
		set_var_((tmp = ft_strdup("intern_canon_off=true")),
			LOC_VAR, VAR_NEUTRAL) : 0;
	ft_memdel((void **)&tmp);
	tmp = ft_strdup("intern_prompt_var=TRUE");
	set_var_(tmp, LOC_VAR, VAR_NEUTRAL);
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&e->line);
	print_curseur(NULL);
	return (0);
}

static int			main_loop_read(t_read *r, t_env *e, int i)
{
	char			buf[MAX_LEN + 1 + 3];

	(!i && is_opt_set(r->opts, 'p')) ? print_curseur(r->prompt) : 0;
	if (is_opt_set(r->opts, 'n') && r->nchars > 0 &&
		(ft_strlen(e->line) == (size_t)r->nchars))
	{
		move_treatment(r);
		return (1);
	}
	ft_bzero(buf, MAX_LEN + 1);
	if ((read(r->fd, buf, MAX_LEN) == -1))
	{
		ft_putstr_fd("read: bad file descriptor", 2);
		return (1);
	}
	if (buf[0] && loop_r_read_treat(buf, r, 0, 0))
		return (1);
	return (0);
}

static int			wrap_timeout(t_read *r, t_env *e, int i)
{
	fd_set					set;
	static struct timeval	timeout;
	int						rv;

	FD_ZERO(&set);
	FD_SET(r->fd, &set);
	(!i) ? timeout.tv_sec = r->timeout : 0;
	timeout.tv_usec = 0;
	rv = select(r->fd + 1, &set, NULL, NULL, &timeout);
	if (rv == -1)
		return (1);
	else if (rv == 0)
		return ((e->last_status = 1));
	return (main_loop_read(r, e, i));
}

void				read__read_display(t_env *e, t_read *r)
{
	int				save_col;
	int				i;

	save_col = e->color_def;
	setup_read_read_display(e, r);
	i = 0;
	(!is_opt_set(r->opts, 'u') && e->fd[2] != -1) ? r->fd = e->fd[2] : 0;
	while (1)
	{
		if (is_opt_set(r->opts, 't'))
		{
			if (wrap_timeout(r, e, i))
				break ;
		}
		else if (main_loop_read(r, e, i))
			break ;
		i++;
	}
	ft_putchar('\n');
	remove_var("intern_prompt_var");
	remove_var("intern_canon_off");
	e->color_def = save_col;
}
