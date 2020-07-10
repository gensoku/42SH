/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_func.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 05:42:24 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/30 05:42:25 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_FUNC_H
# define SH_FUNC_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <pwd.h>
# include <time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/select.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdint.h>
# include "sh_define.h"
# include "sh_struct.h"

/*
** shell init
*/
void			init_env(char **env, t_env *e);
void			set_shlvl(t_env *e);
void			set_sh(t_env *e);
void			set_old_pwd(t_env *e);
void			set_pwd(t_env *e);
void			set_tmp_env(t_env *e);
void			set_exe(t_env *e);
void			ft_set_caps(t_env *e);
void			ft_set_term(struct termios *curent);
int				set_shell_fg(void);

/*
**	line_interpretor
*/
void			read_display(t_env *e, int x);
void			send_instruction(t_env *e);
void			unfinished_line(t_env *e, int type);
void			append_load_ins(t_env *e, int type);
void			moves_display(long x, t_env *e);
void			move_enter(t_env *e);
void			move_del(t_env *e);
void			move_tab(t_env *e);
void			move_ctrl_c(t_env *e);
void			move_left(t_env *e);
void			move_right(t_env *e);
void			move_down(t_env *e);
void			move_up(t_env *e);
void			move_add_(int x, t_env *e);
void			move_ctrl_l(t_env *e);
void			move_cut(t_env *e);
void			move_home(t_env *e);
void			move_paste(t_env *e);
void			move_next_word(t_env *e);
void			move_previous_word(t_env *e);
void			move_end(t_env *e);
void			move_mult_up(t_env *e);
void			move_mult_do(t_env *e);
void			move_tab_spec(t_env *e);
void			move_ctrl_r(t_env *e);
void			move_color_act(t_env *e);

/*
** display
*/
void			print_prompt(t_env *e);
void			print_curseur(char *custom);
void			print_with_end_space(t_env *e);
void			print_comp2(t_env *e, char *join);
void			heredoc_prompt(void);
void			set_current_histo(t_env *e);
void			ft_del_screen(char *line, size_t cur, t_env *e);
void			print_comp(t_env *e);
void			print_curseur_quote(int i);
void			print_current(t_lst_av *tmp);
void			print_tab1_col(char **tab1, int max, int x_max, int col);
void			display_col(t_comp *exe, t_env *e);
void			display_all(char **tab1, t_env *e, int size, int i);
void			print_prompt_quote(int i);
void			ft_print_last_blast(int last);
void			display_error(int n, char *content, t_env *e);
void			display_qu_error(int n);

/*
**	termcaps
*/
void			cursor_add(t_env *e, int x);
void			cursor_less(t_env *e, int x);
void			cursor_reset(t_env *e);
void			cursor_set(t_env *e, t_cursor *cur, char *line);
void			ft_del_spec_screen(t_env *e, int flag);
int				spec_put(int x);
void			reset_print(t_env *e, t_cursor *all);

/*
** completion
*/
int				searcher(t_env *e, int i);
void			interpretor(int x, t_env *e, t_cursor *all);
void			get_inter(t_env *e, t_cursor *all);
int				auto_comp(t_env *e);
int				cls(char *str);
void			aac_p1(t_env *e, char *save);
void			aac_p2(t_env *e);
void			aac_p3(t_env *e, char *save);
t_comp			*get_exe_all(char *name, t_env *e);
t_lst_av		*set_list(t_comp *path);
void			enter(t_env *e);
void			select_cur(t_env *e, t_cursor *all);
void			del_list_av(t_env *e);
void			arrow_left_(t_env *e, t_cursor *all);
void			arrow_right_(t_env *e, t_cursor *all);
void			arrow_up_(t_env *e, t_cursor *all);
void			arrow_down_(t_env *e, t_cursor *all);
void			reset_comp(t_env *e);
char			*get_list_1(char *path, char *name, char *tmp2);
char			*get_list_2(unsigned char type,
	char *name, char *tmp2, char *path);
char			*entry_ch_1(int x, char *name);
t_comp			*entry_ch_3(char **path, char **rest, char *name);
t_comp			*entry_ch_2(char **rest, char **path, char *name, int x);
t_comp			*get_list_3(char *rest, char *name, char *tmp2, t_comp *lst);
t_comp			*get_current_dir(char *tmp2);
t_comp			*get_list_entry(char *path, char *rest, int z);
t_comp			*get_entry_checked(char *name, int x);
t_comp			*get_entry(char *name, char *line);
t_comp			*get_list_spec(char *name, t_env *e, char *path, int z);
t_jobs			*find_job(pid_t pgid);
int				return_search(t_env *e,
	char **last_arg, t_comp *list, char **tab_args);
int				dir_spoted(t_env *e,
	char **path, char **last_arg, t_comp *list);
int				first_case_no_exe(t_env *e, char **last_arg);
int				search_second_case(t_env *e, char **last_arg);
int				ret_sch_free(t_env *e,
	t_comp *list, char **last_arg, char **path);
int				set_free_ret(char **last_arg,
	char **path, t_comp *list, t_env *e);
int				absolute_p(t_env *e,
	char **last_arg, t_comp *list, char **path);
int				get_cur_free(char **last_arg, char **line, t_comp *list);
char			*get_last_arg(char *line);
char			*get_line_qu_hdoc(t_env *e);
t_comp			*get_dir_with_opts(t_env *e,
	char *to_cmp, char *path, int opts);
int				get_type_search(char *line);
char			*add_slash_free(char *line, int opts);

/*
** instruction
*/
void			instruction(char *line, int sub_flag, t_env *e);
void			check_redir_exec(t_env *e, t_token *tmp);
int				heredoc_launcher(t_token *node, t_env *e, int i);
void			check_close_fd_redir(t_token *lst, t_env *e);
void			del_list_redir(t_env *e);
void			add_background_to_process(t_token *list);

/*
** execution
*/
void			root_tok(t_token *node, t_env *e);
int				exec_tok(char *save, t_env *e, int flag);
int				check_exec_tok(char *save, t_env *e);
int				check_valid_tok(t_token *node, t_env *e);
int				execve_fork(t_env *e, char *name, char **tab1, char *full_name);
int				adv_exec(t_env *e, char *name, char **tab1, int flag);
void			adv_exec_set_fds(t_env *e);
int				adv_check_valid(t_exe **tmp, char *name, char **tab1, t_env *e);
int				adv_exec_invalid(t_env *e, int update_stat);
int				check_stats_type(char *name, t_env *e);
t_exe			*get_exe_list(char *name, t_env *e);
t_exe			*get_exe_hash(char *name, t_env *e);
void			resume_state(t_env *e, int opt, t_token *tmp);
void			setup_background(t_token *tmp,
	t_env *e, int *flag_stop, t_token *node);
void			sub_setup(t_token *unused,
	t_env *e, int *flag_stop, t_token *node);
void			setup_pi(t_token *tmp, t_env *e, int *flag_stop, t_token *node);
void			setup_and_or(t_token *tmp, t_env *e,
void			(*func)(t_token *t, char *s, t_env *e), t_token *node);

/*
**	parser line / token
*/
char			**strsplit_command(char *str, t_env *e);
t_comp			*norm_get_err(char *str, t_comp *list, t_tools *t, int opt);
char			**ft_strsplit_spec(char *str, int opt);
void			parser_token(char *line, t_env *e, int agreg);
int				ft_istoken(char *line, int i, t_parser *tf, t_env *e);
int				parser_left_(char *str, int x, t_parser *tf);
int				parser_right_(char *str, int x, t_parser *tf);
int				parser_r_agreg_(char *str, int x, t_parser *tf);
int				parser_l_agreg_(char *str, int x, t_parser *tf);
int				loop_create_token(char *line,
		t_env *e, t_parser *tf, int agreg);
void			loop_args_token(t_parser *tf, char *line);

/*
** checking quoting flags char by char
*/
int				check_quote(t_env *e);
int				set_sep_flags(char *tmp, int i, int *flags, t_quote *count);
int				chk_dqu(char *tmp, int i, int *flags, t_quote *count);
int				chk_less_dqu(char *tmp, int i, int *flags, t_quote *count);
int				chk_qu(char *tmp, int i, int *flags, t_quote *count);
int				chk_less_qu(char *tmp, int i, int *flags, t_quote *count);
int				chk_xor_bqu(char *tmp, int i, int *flags, t_quote *count);
int				chk_pr(char *tmp, int i, int *flags, t_quote *count);
int				chk_less_pr(char *tmp, int i, int *flags, t_quote *count);

/*
** job control
*/
void			wait_pgid(pid_t pgid, t_env *e, int opt);
pid_t			wait_process(t_env *e, int opt);
void			suspend_2(void);
t_childs		*jobs_getter__bypid(pid_t pid, t_env *e);
t_childs		*jobs_setter__last(t_childs *tmp, pid_t pid);
t_childs		*jobs_getter__bylast(t_childs *head, int type);
t_childs		*jobs_getter__bypgid(pid_t pgid, t_env *e);
void			jobs_print__event(t_childs *tmp, t_sigevent event);
void			jobs_destruct__last(t_childs **node);
void			jobs_destruct__bypid(pid_t pid, t_env *e);
void			jobs_setter__reset(t_childs *tmp, int jump);
void			jobs_setter__upgr(t_childs *head, int type);
void			print_jobs_l(t_childs *tmp, t_env *e, int i, int z);
void			print_jobs_p(t_childs *tmp, t_env *e, int i, int z);
void			print_jobs_(t_childs *tmp, t_env *e, int i, int z);
void			ft_print_jobs(int z);
void			reset_signals(void);
void			init_term_grp(pid_t pgid, pid_t pid, int foreground);
void			wait_resume_ctrl_z(t_env *e, pid_t pid, int type, char **name);
int				signal_block(int sig);
int				signal_unblock(int sig);
void			signal_child(int sig);
void			suspend();
void			no_exit();
void			resize();
void			set_signals(void);
int				stopped_or_bg(t_env *e);

/*
** tools
*/
t_comp			*backslash_lst(t_comp *lst);
char			**t_comp_to_tab(char **new, t_comp *list_elem);
int				size_list_t_comp(t_comp *lst);
t_spath			*add_exe(t_spath *lst, char *path);
t_env			*get_e(t_env *env);
int				ft_is_point(char *str);
char			*ft_convert_space(char *str, int i, int j, int k);
size_t			ft_strlen_char(char *str, char c);
void			ft_del_tab(char **tab1);
char			*ft_implode(char **tab1, char c);
void			ft_putspace(int nb, int max);
void			code_exit(t_env *e);
int				get_size_len(char **tab1);
mode_t			get_rights();
void			checks_tild(char *str, t_env *e, char **to_free);
char			*get_env(char *str, char **env, int case_sensitivse);
t_parser		*get_helper_tf(void);
int				get_size_prompt(char *current);
int				chk_tsp(char *str);
int				check_back_from(char *str, int i);
void			save_histo_(t_env *e, char *tmp);
char			*add_backslash(char *str, int type, int i);
int				is_symbol_(char c);
t_agreg			*set_agreg(void);
void			reset_agreg(t_agreg *t, int opt);
int				typedefineargs(int n);
t_pars_cut		*get_helper_cut();
t_tools			*get_helper_tools_(void);
int				set_ret_error(int n, char *name);
void			tool_incr_(int *x, int *z, t_parser *tf, int opt);
int				get_size_childs(t_childs *childs);
void			set_color_type(int type);
void			reset_fd_(t_env *e);
int				g_sts_f(char *path, int type);
int				get_type_prompt(int flag, t_quote *count);
void			ft_exit_sub(int n, t_env *e, int opt);
char			**ft_tab_dup(char **src);
int				ft_len_tab(char **tab1);
void			update_ret_value(t_env *e);
char			*ft_get_file(char *path, int fd);
char			**ft_add_to_tab(char **array, char *add, char **add_tab);
char			**ft_del_from_tab(char **array, char *to_del);
void			ft_put_tab_fd(char **array, int fd, char c);
char			*get_env_line(char **array, char *line);
int				is_relative_path(char *path);
char			*get_back_path_link(t_env *e, char *arg);
char			*get_relative_slash(char *arg, char *path);
void			*p_try(size_t size, t_env *e);
char			*where_are_we(void);
int				ft_size_int(int n);
void			read_add_bkslsh(char **line, char *to_slsh);
char			*ft_dup_free(char *to_free, char *to_dup);
t_cursor		*cpy_cursor(t_cursor *cur);
t_quote			*cpy_quote(t_quote *cur);
int				ft_isnum_str(char *str);

/*
**	args parser
*/
int				check_opts(char *av,
	char *opts, unsigned long *flags, int opts_flags);
int				is_opt_set(unsigned long flags, char a);
int				check_opt_conflict(unsigned long opts, char *to_check);
unsigned long	opts_get_static(unsigned long value);
void			debug_opts(unsigned long flags, char *opts);
char			get_opt_arg(unsigned long opts, char *args, int flag);

/*
**  contructor
*/
t_comp			*push_back_comp(char *name, t_comp *lst, int type);
t_comp			*add_comp_ex_(t_comp *node, t_comp *lst);
t_childs		*push_front_child(pid_t son,
	t_env *e, char *name, int foreground);
int				push_front_child_id(t_childs *tmp, t_childs *head, int max);
t_comp			*push_back_elem_(char *str, t_comp *list, int typed);
t_histo			*push_front_histo(t_env *e, char *line2);
void			push_back_redir(t_env *e, char *token, char *path);
int				push_back_reg(char *str, t_tmp_env **list);
void			push_front_token(char *tok, t_parser *tf, t_env *e);

/*
**  destructor
*/
void			ft_del_comp_exe(t_env *e);
void			ft_del_comp_path(t_env *e);
void			destruct_child(t_env *e);
void			del_t_exe(t_exe *lst);
void			del_t_spath(t_spath *lst);
void			del_t_comp(t_comp *lst);
void			del_t_histo(t_histo *lst);
void			del_t_childs(t_childs *lst);
void			del_t_lst_av(t_lst_av *lst);
void			del_all_tokens(t_token *lst);
void			del_parser_tf(t_parser *tf);
void			destructor_file(t_redir *list, t_env *e);
void			del_tmp_env(t_env *e);
void			del_t_pars_cut(t_pars_cut *t);
void			del_t_tools_(t_tools *t);
void			d_all_var(t_loc_var *vars);
void			del_history(t_history **h);

/*
**	redirections/operators
*/
void			run_tok_left2(t_env *e, char *path);
void			run_pipe(t_token *node, char *save, t_env *e);
void			check_set_count_pipe(void);
int				run_tok_left(t_token *node);
int				run_tok_right(t_token *node);
int				run_tok_right2(t_token *node);
int				link_tok_left(t_token *node, t_env *e);
int				link_tok_right(t_token *node, t_env *e);
int				link_tok_right2(t_token *node, t_env *e);
int				check_type_redir(t_token *node);
int				read_display_2(int x, t_env *e, t_redir *tmp);
void			run_and(t_token *node, char *save, t_env *e);
void			run_or(t_token *node, char *save, t_env *e);
int				run_right_agreg(t_token *node, t_env *e);
int				run_left_agreg(t_token *node, t_env *e);
int				link_right_agreg(t_token *node, t_env *e);
int				link_left_agreg(t_token *node, t_env *e);
void			get_full_redir_r(t_token *node, t_agreg *ag);

/*
**	builtins
*/
char			*ft_get_pwd(void);
void			ft_pwd(char **tab1, t_env *e);
void			ft_cd(char **tab1, t_env *e);
void			builtin_setup_error(char *msg, t_env *e, int status);
void			cd_no_arg(char **tmp2, t_env *e);
void			cd_double_args(char **tab1, char **tmp2, char *tmp3, t_env *e);
void			cd_with_opts(t_env *e,
	unsigned long opts, char *cmd, char **wtf);
void			ft_unsetenv(char **tab1, t_env *e);
void			ft_setenv(char **tab1, t_env *e);
void			ft_print_env(t_env *e);
void			ft_exit(int n, t_env *e, int opt);
void			check_exit(char **tab1, t_env *e);
void			ft_echo(char **argv, t_env *e);
int				get_builtin(char **array, t_env *e, t_fexec exec);
void			ft_jobs(char **tab1, t_env *e);
int				ft_built_var(char **array, t_env *e);
int				check_before_equal(char *str, char *to_check);

/*
**	builtin read
*/
void			ft_read(char **array, t_env *e);
int				p_read_err(char *line, int type_err, char c);
int				set_read_args(t_read *r, unsigned long opts);
int				wrong_read_name(char *line, int opts);
int				pre_check_args(char **array, int i);
int				opts_w_arg_chk(unsigned long opts, char *line);
int				opt_with_arg(unsigned long opts, char *all_opts_arg);
void			read__read_display(t_env *e, t_read *r);
int				mo_r_display(int x, t_read *r);
int				move_treatment(t_read *r);
void			read_into_array(t_read *r);
void			read_into_args(t_read *r);
int				r_move_ctrl_c(t_env *e);
void			r_move_add_(int x, t_env *e, int silent);
void			r_move_ctrl_l(t_env *e, int silent);
void			r_move_cut(t_env *e, int silent);
void			r_move_del(t_env *e, int silent);
void			r_move_end(t_env *e, int silent);
void			r_move_home(t_env *e, int silent);
void			r_move_left(t_env *e, int silent);
void			r_move_mult_do(t_env *e, int silent);
void			r_move_mult_up(t_env *e, int silent);
void			r_move_next_word(t_env *e, int silent);
void			r_move_paste(t_env *e, int silent);
void			r_move_previous_word(t_env *e, int silent);
void			r_move_right(t_env *e, int silent);

/*
**	builtin ENV
*/
void			check_loop_env(char **tab1, t_env *e);
void			ft_print_env(t_env *e);
void			display_verbose_lvl(int nb);
void			add_to_local_env(t_env *e, char **args, unsigned long opts);
int				verbose_lvl(int option);
int				how_many_char(char *str, char c);
int				env_opt_s(t_env *e, char *str, unsigned long *opts);
int				env_opt_u(t_env *e, char *arg, unsigned long *opts);
int				env_opt_p(t_env *e, char *str, unsigned long *opts);
t_exe			*get_exe_alt_paths(char *name, t_env *e);
void			check_verbose_env_p(t_exe *matched, t_env *e, char **args);
int				env_bui_call(t_env *e, char **array, unsigned long opts);
int				env_exec_call(t_env *e, char **array, unsigned long opts);
int				check_error_opts(char **tab1,
	int ret, unsigned long opts, t_env *e);
void			env_error(char *msg, int illegal, char opt);
int				reset_stuff(t_env *e, int status);

/*
** fg builtin
*/
int				jobs_cmd__signal(t_childs *proc, t_env *e, t_jobscmd cmd);
int				jobs_cmd__number(char *arg, t_env *e, t_jobscmd cmd);
void			jobs_cmd__print(t_jobscmd cmd, int fd);
void			jobs_cmd(char **array, t_env *e, t_jobscmd cmd);
void			built_fg(char **array, t_env *e);
void			built_bg(char **array, t_env *e);
int				job_is_stoped(t_jobs *job);
int				job_is_completed(t_jobs *job);
void			ft_export(char **arg, t_env *e);
void			ft_unset(char **arg, t_env *e);

/*
**	export builtin
*/
int				check_error_exp(char *str, int *opt);
int				check_opt_exp(char *str, int *opt);
void			check_for_set(char *line);
void			export_to_setenv(char *line, char **setter, char *cut);
void			ft_put_exp_error(char *str, int *opt);
int				is_var_(char *key);
void			display_var_p(char *key, int opt);
void			display_var_no_p(void);
void			reset_var(char *str, t_loc_var *setter);
int				remove_var(char *str);

/*
** local var
*/
void			set_var_(char *line, int type, int status);
t_loc_var		*get_last_var(void);
t_loc_var		*get_var_ptr(t_env *e, char *key, int sensitive);
void			set_loc_var_env(t_env *e);
int				loc_var_rep(t_env *e, char **line, int i, int k);
int				check_dollar_end(char *str, int i);
void			check_replace_back_quote(char **line, t_env *e);
void			bq_check_setup(char **line, int *i, int *k, char **str);
int				update_var(char *key, char *val, t_env *e);

/*
** globbing
*/
char			*build_list_reg(t_tmp_env *cmd);
void			ft_del_reg(t_tmp_env **p);
bool			ft_regex(char *p, char *s);
t_regex			*ft_regex_compile(char *s);
bool			ft_matchhere(t_regex *r, char *s);
int				ft_check_hidden_file(char *pattern);
char			*ft_get_actual_regex(char *regex);
char			*ft_get_next_regex(char *regex);
bool			ft_ignore(char **av, size_t n);
int				ft_readdir(char *path, char *pattern, t_tmp_env *list);
char			*globing_handler(char *line, t_env *e);
int				is_dir(char *path);
int				ft_is_multiple_regex(char *regex);

/*
**  hashtable
*/
void			move_reset_hash(t_env *e);
unsigned long	do_hash(char *full_path, size_t hash_size);
void			set_hash(t_env *e);

/*
**  syntax color
*/
void			checks_syn_col(t_env *e, char *arg, t_cursor save, int opts);
int				is_a_tok(char c);
void			ft_del_spec_screen_lined(t_env *e, int flag, t_cursor *ref);
void			check_bord_term(t_env *e);

/*
** Builtin : history
*/
void			built_history(char **arg, t_env *e);
char			*built_history__path(void);
void			built_history__catch(char *cmd);
int				built_history__print(t_history *history, t_env *e);
int				built_history__read(t_history *history, int history_fd);
int				built_history__parse(t_history *history);
t_hentries		*built_history__hentries_add(t_history *history,
	t_hentries *entry);
t_hentries		*built_history__hentries_end(t_hentries *entries);
t_hentries		*built_history__hentries_new(void);
int				built_history__check_cmd(char *cmd);
int				built_history__error(t_herror error);
int				check_history_replace(t_env *e, int i);
char			*built_history__replace(t_history *history, t_env *e);
int				hist_setup_replace(int i, int k, char **line);

#endif
