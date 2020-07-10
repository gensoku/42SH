/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_exe_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 09:27:26 by tsedigi           #+#    #+#             */
/*   Updated: 2017/02/22 02:47:00 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_func.h"

static void		child_exe(t_env *e, int fds[2], char *save)
{
	reset_signals();
	close(fds[0]);
	init_term_grp(e->tmp_pgid, getpid(), e->foreground);
	(e->ag_fd[0] != -1) ? dup2(fds[1], e->ag_fd[0]) : 0;
	(e->ag_fd[1] == -1 || e->ag_fd[1] == 1) ? dup2(fds[1], STDOUT_FILENO) : 0;
	(e->fd[0] != -1) ? dup2(e->fd[0], STDOUT_FILENO) : 0;
	(e->fd[1] != -1) ? dup2(e->fd[1], STDERR_FILENO) : 0;
	(e->fd[2] != -1) ? dup2(e->fd[2], STDIN_FILENO) : 0;
	(e->flag_pipe) ? dup2(e->flag_pipe, STDIN_FILENO) : 0;
	exec_tok(save, e, (save && save[0] == '(') ? 2 : 0);
	exit(e->last_status);
}

static void		parent_exe(t_env *e, int fds[2], t_token *node)
{
	reset_signals();
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	init_term_grp(e->tmp_pgid, getpid(), e->foreground);
	exec_tok(node->second, e, 0);
	exit(e->last_status);
}

static void		setup_synchro(pid_t son, t_env *e, char *save)
{
	(!e->tmp_pgid) ? e->tmp_pgid = son : 0;
	init_term_grp(e->tmp_pgid, son, e->foreground);
	push_front_child(son, e, save, e->foreground);
	e->childs->grpid = getpgid(son);
}

static void		after_child(t_token *node, int fds[2], t_env *e)
{
	pid_t		son2;

	if (node->previous)
	{
		e->flag_pipe = fds[0];
		root_tok(node->previous, e);
		close(fds[0]);
		return ;
	}
	else if (node->type == P_REDIR && !check_exec_tok(node->second, e))
	{
		son2 = fork();
		(son2 == -1) ? display_error(-1, "fork failed exit", e) : 0;
		(son2 == 0) ? parent_exe(e, fds, node) : 0;
		setup_synchro(son2, e, node->second);
		close(fds[0]);
	}
	else if (node->type == P_REDIR)
		exec_tok(node->second, e, 0);
	check_set_count_pipe();
}

void			run_pipe(t_token *node, char *save, t_env *e)
{
	pid_t			son;
	int				fds[2];

	if (!save)
		return ;
	pipe(fds);
	son = fork();
	signal_block(SIGCHLD);
	e->pipe_builtin = 1;
	(son == -1) ? display_error(-1, "fork failed exit", e) : 0;
	tcsetattr(0, TCSANOW, &e->oterm);
	(son == 0) ? child_exe(e, fds, save) : 0;
	close(fds[1]);
	setup_synchro(son, e, save);
	after_child(node, fds, e);
}
