/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 11:04:22 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/16 11:00:46 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static	void	set_tmp_norm(t_redir *tmp, t_env *e)
{
	e->heredoc.end_file_tog = 1;
	e->heredoc.end_file = ft_strdup(tmp->token);
	e->heredoc.end_file_confirm = NULL;
	heredoc_prompt();
}

static	t_redir	*end_file_norm(t_redir *tmp, t_env *e)
{
	if (e->heredoc.end_file_tog == 0)
	{
		run_tok_left2(e, tmp->path);
		(e->heredoc.end_file_confirm) ?
			ft_memdel((void **)&e->heredoc.end_file_confirm) : 0;
		if (tmp->next)
		{
			heredoc_prompt();
			tmp = tmp->next;
			ft_memdel((void **)&e->line);
			e->heredoc.end_file = ft_strdup(tmp->token);
			e->heredoc.end_file_tog = 1;
		}
		else
			return (NULL);
		return (tmp);
	}
	return (tmp);
}

static	int		buf_end_file(t_env *e)
{
	ft_putchar('\n');
	e->heredoc.end_file_tog = 0;
	(e->heredoc.end_file_confirm) ?
		ft_memdel((void **)&e->heredoc.end_file_confirm) : 0;
	destructor_file(e->left_redir, e);
	return (-2);
}

static	void	set_norm_here_loop(t_env *e, int x)
{
	if (x == 4 && !ft_strcmp(e->heredoc.end_file, "EOF"))
	{
		e->save_type = 155;
		move_enter(e);
	}
}

int				read_display_2(int x, t_env *e, t_redir *tmp)
{
	char		buf[4];

	ft_bzero(&buf, 4);
	ft_memdel((void **)&e->line);
	cursor_set(e, e->cursor, e->line);
	e->color_def = 0;
	if (!tmp)
		return (-1);
	set_tmp_norm(tmp, e);
	while (1337)
	{
		while (buf[0] != 4)
		{
			ft_bzero(&buf, 4);
			read(0, buf, 4);
			x = (buf[3] << 24) + (buf[2] << 16) + (buf[1] << 8) + buf[0];
			set_norm_here_loop(e, x);
			moves_display(x, e);
			if ((tmp = end_file_norm(tmp, e)) == NULL)
				return (0);
			if (x == 4 || x == 3)
				return (buf_end_file(e));
		}
	}
	return (-1);
}
