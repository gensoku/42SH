/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_define.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 11:22:25 by tsedigi           #+#    #+#             */
/*   Updated: 2017/03/30 05:42:12 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_DEFINE_H
# define SH_DEFINE_H

# define YELLOW						"\e[33;1;m"
# define RED						"\e[31;1;m"
# define GREEN						"\e[32;1;m"
# define BLUE						"\e[34;1;m"
# define MAGENT						"\e[35;1;m"
# define CYAN						"\e[36;1;m"
# define WHITE						"\e[37;1;m"
# define BLACK						"\e[30;1;m"

# define BG_YELLOW					"\e[43m"
# define BG_RED						"\e[41m"
# define BG_GREEN					"\e[42m"
# define BG_BLUE					"\e[44m"
# define BG_MAGENT					"\e[45m"
# define BG_CYAN					"\e[46m"
# define BG_WHITE					"\e[47m"
# define BG_BLACK					"\e[40m"
# define RESET						"\033[0m"

# define YELLOW_H					"\e[33m"
# define RED_H						"\e[31m"
# define GREEN_H					"\e[32m"
# define BLUE_H						"\e[34m"
# define MAGENT_H					"\e[35m"
# define CYAN_H						"\e[36m"
# define WHITE_H					"\e[37m"
# define BLACK_H					"\e[30m"

# define CUS_SHELL					"[42sh]"
# define SH_NAME					"42sh"

# define MAX_PROMPT_LEN				40
# define FLAG_QU 					1
# define FLAG_DQU	   	  			2
# define FLAG_BACK	   	  			4
# define FLAG_PAR					8
# define FLAG_BQU					16

# define MAX_LEN					4094

# define TOK_QUOTED					1
# define TOK_DQUOTED				2
# define TOK_WORD					3

# define COL_EN						1

# define R_REDIR 					1
# define R_D_REDIR					2
# define L_REDIR					4
# define L_D_REDIR					8
# define L_AGR_REDIR				16
# define R_A_RED					32
# define P_REDIR					64
# define OR_RE						128
# define AND_RE						256
# define BACK_PROCESS_REDIR			512
# define SUB_RED					1024

# define MAX_L_FD					4863
# define MAX_R_FD					18

# define FLAG_L		   	   			1
# define FLAG_N	 	  	   			2
# define FLAG_P		   	   			4
# define FLAG_R		   	   			8
# define FLAG_S		  	  			16
# define FLAG_H 					32

# define FLAG_A_		   			1
# define FLAG_D_	 	  			2
# define FLAG_E_		   			4
# define FLAG_N_		   			8
# define FLAG_P_		   			16
# define FLAG_R_  	   	  			32

# define VAR_R 						1
# define VAR_X 						2
# define VAR_NEUTRAL				4

# define ENV_VAR					1
# define LOC_VAR					2
# define TMP_VAR					3

# define ER_SEND 					32
# define ER_EXP4 					64
# define ER_EXP5 					128
# define ER_EXP6 					256
# define ER_EXP7 					512
# define ER_EXP8 					1024

# define CASE_TRUE					1
# define CASE_FALSE					0

# define SUB_FALSE					0
# define SUB_TRUE					1

# define SET_OPTS					1
# define XOR_OPTS					2
# define SUPR_OPTS					4
# define LAST_OPTS					8

# define FIRST_ARG					1

# define ADD_VERBOSE				0
# define RESET_VERBOSE				1
# define VERB_VAL 					2

# define POISON						0xffffff
# define OPT_WALL_MAX				0xffffffffffffffff

# define F_BLK						1
# define F_CHR 						2
# define F_DIR						3
# define F_FIFO 					4
# define F_SYMLINK					5
# define F_REG 						6
# define F_SOCK						7

# define F_GET_TYPE					1
# define F_GET_NLNK					2
# define F_GETLNK_TYPE				4

# define GET_FULL_DIR				1
# define GET_DIR_PATH				2

# define MAX_SYM_FOLOW				10

# define SYN_LAST_WORD				1
# define SYN_ADD					1
# define SYN_DEL					2

# define BUI_READ_OPTS				"ersutpandcall"
# define BUI_READ_CONF				"adnput"
# define R_DIGIT_OPT				"tun"
# define R_ALPHA_OPT				"a"
# define ASC_FORMAT					1
# define DIGIT_FORMAT				2
# define ALNUM_FORMAT				4

# define W_EXITED					1
# define W_SIGNALED					2
# define W_STOPPED					4

# define IN(c, r)					(ft_is_in_list(c, NULL, r))
# define MATCH(r, s)				(r->type == DOT || *s == r->c || IN(*s, r))
# define FSUB(x, y)					ft_strsub(x, 0, y)
# define REGEX_LIST					("*?+[]{}|")
# define R_PATH(x)					((*x == '/') ? "/" : ".")
# define R_HERE(x)					(ft_get_actual_regex(x))
# define R_NEXT(x)					(ft_get_next_regex(x))
# define R_LAST(x, y)				(ft_get_last_regex(x, y))
# define BASH_HIDDEN_DISPLAY		(0)
# define CHECK_SL(x, y)				(check_back_from(x, y) % 2)
# define FAST_ER(x)					(ft_putendl_fd(x, 2))
# define LEN_(x)					(ft_strlen(x))
# define CONTEXT					(get_e(NULL))
# define CTX(R)						(CONTEXT->R)
# define WCH_FD						(CTX(fd)[0] == -1 ? 1 : CTX(fd)[0])

# define E_F						e->flag
# define E_ERR						e->errno_du_pauvre
# define E_LI						e->line
# define E_SQ						e->save_quote
# define FD_T_R						t->right_val
# define FD_T_L						t->left_val

# define ASSIGN_BIT(x)				((1L << x))
# define VALUE_ALPHA_BIT(x)			((x < 97) ? x - 65 : x - 97 + 26)

# define ERROR_RW_FILE	": cannot read/create file"
# define ERROR_R_FILE 	": cannot open file"
# define ERR_RAG 		": error on >& couldn't open/create file"
# define ERR_AMB		": ambiguous redirect"
# define ERR_FD			": Bad file descriptor"
# define ERR_CMD		": Command not found"

# define TEMPO 		"/tmp/.fTeMp0a8b7c2d2z"
# define TEMPO_BQ 	"/tmp/.fTeMp0a81op16fd1652d2z"
# define ERR_ST "error with advanced completion (terminal probably too short)."
# define ERR_IO "ioct call failed unknow term capacity, exit"
# define E_SP 	"syntax error near unexpected token `;;'"
# define E_SS	"syntax error near unexpected token `;'"
# define E_BG	"syntax error near unexpected token `&'"
# define E_SB	"syntax error near '('"
# define E_SY	"syntax error"
# define SH_INI "Couldn't put the shell in its own process group"

# define EXP_ER_OPT "export: usage: export [-p] [name[=value] ...]"

# define HISTORY_BUFLEN 			2048
# define HISTORY_FILENAME			".42sh_history"
# define HISTORY_FILENAME_ZSH		".zsh_history"
# define ABS(x)						-(x)

# define HIST_ERR_STRUCT			"history: error on structure"
# define HIST_ERR_FILE				"history: history file error"
# define HIST_ERR_PARSE				"history: history file parsing error"

#endif
