/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 05:42:16 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/30 05:42:17 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_STRUCT_H
# define SH_STRUCT_H

typedef enum						e_sigevent
{
	E_DONE = 2,
	E_SIGSTOPPED = 1,
	E_SIGTERMINATED = 0
}									t_sigevent;

typedef enum						e_fexec
{
	EXEC = 1,
	NO_EXEC = 0
}									t_fexec;

typedef enum						e_type
{
	BEGIN = 0,
	END,
	DOT,
	STAR,
	PLUSS,
	QUEST,
	LIST,
	CHAR,
}									t_type;

typedef enum						e_htype
{
	HISTORY_ALL = 0,
	HISTORY_OFFSET = 1,
	HISTORY_REPLACE = 2,
	HISTORY_PERMUTE = 3
}									t_htype;

typedef enum						e_herror
{
	HISTORY_NOT_FOUND = -2,
	HISTORY_TOO_MANY_ARG = -3,
	HISTORY_EMPTY_ARG = -4,
	HISTORY_OPT_ILLEGAL = -5
}									t_herror;

typedef enum						e_jobscmd
{
	JOBS_FG = 2,
	JOBS_BG = 3
}									t_jobscmd;

typedef struct						s_hentries
{
	long long int					id;
	char							*time;
	char							*state;
	char							*cmd;
	struct s_hentries				*next;
}									t_hentries;

typedef struct						s_history
{
	t_htype							type;
	long long int					total;
	long long int					offset;
	char							*raw;
	t_hentries						*entries;
}									t_history;

typedef struct						s_agreg
{
	char							*spliter;
	char							*left;
	char							*right;
	char							*cut;
	int								left_val;
	int								right_val;
	int								close;
}									t_agreg;

typedef struct						s_tools
{
	int								i;
	int								flag_sp;
	int								flag_on;
	int								k;
	int								count_bq;
	int								count_pr;
	char							tok;
}									t_tools;

typedef struct						s_parser
{
	char							*tok;
	char							*arg1;
	char							*arg2;
	int								flag;
	int								ret;
	int								agreg_int;
	int								i;
	int								type;
	int								back_flag;
}									t_parser;

typedef struct						s_pars_cut
{
	int								i;
	int								flag_on;
	char							tok;
	char							*tmp_str;
}									t_pars_cut;

typedef struct						s_lst_av
{
	char							*name;
	int								current;
	int								selected;
	struct s_lst_av					*next;
	struct s_lst_av					*previous;
}									t_lst_av;

typedef struct						s_comp
{
	char							*name;
	int								type;
	struct s_comp					*next;
}									t_comp;

typedef struct						s_histo
{
	char							*name;
	struct s_histo					*next;
	struct s_histo					*previous;
}									t_histo;

typedef struct						s_exe
{
	char							*name;
	char							*path;
	char							*full_name;
	struct s_exe					*next;
}									t_exe;

typedef struct						s_spath
{
	char							*name;
	struct s_spath					*next;
	t_exe							*list;
}									t_spath;

typedef struct						s_childs
{
	int								id;
	pid_t							child;
	pid_t							grpid;
	int								status;
	char							done;
	char							stopped;
	int								last;
	int								foreground;
	int								running;
	char							*name;
	struct s_childs					*next;
}									t_childs;

typedef struct						s_jobs
{
	char							*command;
	struct s_jobs					*next;
}									t_jobs;

typedef struct						s_cursor
{
	int								row;
	int								col;
	int								total;
}									t_cursor;

typedef struct						s_quote
{
	int								pr;
	int								bq;
	int								ac;
}									t_quote;

typedef struct						s_token
{
	char							*tok;
	char							*first;
	char							*second;
	char							*errno_node;
	int								fd;
	int								type;
	int								exec;
	int								pgid;
	int								foreground;
	t_jobs							*jobs;
	int								p_count;
	struct s_token					*next;
	struct s_token					*previous;
	struct s_token					*next_call;
}									t_token;

typedef struct						s_redir
{
	char							*path;
	char							*token;
	struct s_redir					*next;
}									t_redir;

typedef	struct						s_tmp_env
{
	char							*value;
	struct s_tmp_env				*next;
}									t_tmp_env;

typedef struct						s_regex
{
	t_type							type;
	char							c;
	bool							not;
	char							list[100];
	size_t							i;
	struct s_regex					*next;
}									t_regex;

typedef struct						s_loc_var
{
	int								type;
	int								status;
	int								empty;
	char							*key;
	char							*value;
	struct s_loc_var				*next;
}									t_loc_var;

typedef	struct						s_heredoc
{
	int								end_file_tog;
	char							*end_file;
	char							*end_file_confirm;
}									t_heredoc;

typedef struct						s_read
{
	unsigned long					opts;
	char							delim;
	char							*a_arr;
	char							*prompt;
	int								fd;
	int								nchars;
	int								timeout;
	char							**args;

}									t_read;

typedef struct						s_env
{
	int								flag_env;
	int								opt;
	int								std_fd[3];
	int								last_status;
	t_heredoc						heredoc;
	int								sub_shell;
	int								display_bg;
	char							**env;
	int								envi;
	int								code_exit;
	int								pipe_builtin;
	char							*current;
	char							*home;
	char							*prev_histo;
	char							*saved_histo;
	int								col;
	int								row;
	int								interactive;
	char							*cut;
	struct termios					oterm;
	struct termios					term;
	char							*line;
	t_cursor						*cursor;
	t_histo							*histo;
	t_histo							*tmp_histo;
	int								hshell;
	t_spath							*paths;
	t_spath							*alternate_paths;
	char							*alt_path_line;
	int								altpath;
	t_comp							*comp_exe;
	t_comp							*comp_path;
	t_childs						*childs;
	t_childs						*current_proc;
	char							*save_quote;
	int								flag;
	t_quote							*count_qu;
	char							*comp_current;
	int								comp_screen;
	t_lst_av						*auto_c;
	t_lst_av						*cur_node;
	char							*ret_comp;
	int								stop_comp;
	t_token							*split_tok;
	t_redir							*left_redir;
	char							*errno_du_pauvre;
	char							*agreg_tmp;
	int								save_type;
	int								fd[3];
	int								ag_fd[3];
	int								term_fd;
	int								proc_state;
	int								color_def;
	t_exe							**hash;
	size_t							hash_size;
	pid_t							cur_proc;
	int								fd_debug;
	int								foreground;
	int								heredoc_null;
	pid_t							tmp_pgid;
	int								flag_pipe;
	t_tmp_env						*tmp_env;
	char							**local_env;
	char							*cur_direc;
	t_loc_var						*all_var;
}									t_env;

typedef	struct						s_red_func
{
	int								code;
	int								(*f)(t_token *, t_env *);
}									t_red_func;

typedef void						(*t_set_func)\
	(void *, void *, void *, void *);

typedef struct						s_set_funcs
{
	int								code;
	t_set_func						f;
}									t_set_funcs;

typedef	void	(*t_builtin__func)(char **, t_env *);

typedef struct						s_builtins
{
	const char						*builtin_name;
	t_builtin__func					builtin_func;
}									t_builtins;

#endif
