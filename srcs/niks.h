/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   niks.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nhariman <nhariman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 16:24:35 by nhariman      #+#    #+#                 */
/*   Updated: 2020/11/28 15:29:37 by nhariman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIKS_H
# define NIKS_H

# define SQ 1
# define DQ 2
# define NQ 3

typedef struct	s_gnl
{
	int				bytes_read;
	int				fd;
	char			*line_read;
}				t_gnl;

typedef	struct	s_trim
{
	int			start;
	char		*res;
}				t_trim;

/*
** dq: checks for equal amount of double quotes " "
** sq: checks for equal amount of single quotes ' '
*/

typedef struct	s_qts
{
	int			dq;
	int			sq;
}				t_qts;

/*
**	int			echo;	- echo command was used
**	int			env;	- env command was used
**	int			exec;	- exec command was used
**	int			exp;	- export command was used
**	int			pwd;	- pwd was used
*/
typedef struct	s_check
{
	int			echo;
	int			env;
	int			exp;
	int			exec;
	int			err;
	int			pwd;
	int			rd;
}				t_check;

typedef struct	s_shell
{
	t_check		check;
	int			exit_code;
	int			fd;
	int			oldnb;
	char		*cmd;
	char		*echo;
	char		*pwd;
	char		**argv;
	char		**env;
	char		*env_s;
	char		*rd_r;
	char		*err;
	char		*exprt;

}				t_shell;

/*
** general functions
*/

char			*ft_rm_endline(char *str);
char			*gnl_strjoin(char *s1, char *s2);
char			*ft_strjointwo(char *s1, char *s2);
void			ft_find_arg(char *str, int *i);
int				get_next_line(int fd, char **line);
char			*ft_charjoin(char *str, char c);
char			*ft_make_single_char_str(char c);
char			**ft_argv(char *str, t_shell *shell);
int				ft_count_arr(char *str);
int				ft_arrlen(char **arr);
char			**ft_add_arr_front(char **arr, char *input);
char			**ft_add_arr_back(char **arr, char *input);
void			ft_free_array(char **arr, int len);
char			**empty_array(char *cmd);
void			ft_malloc_fail(void);

/*
** quotes parsing.
*/

void			ft_strspecial(char *str, t_trim *trim, int *i, char c);
void			ft_parse_dollar(char *str, int *i,
							t_trim *trim, t_shell *shell);
char			*ft_doublequotes_str(char *str, int *i, t_shell *shell);
char			*ft_no_quotes_str(char *str, int *i, t_shell *shell);
char			*ft_singlequotes_str(char *str, int *i);
int				ft_qt_check(char *line, int *i, int type, t_qts *qts);

/*
** checks for correct input before parsing.
*/

void			ft_set_qts(t_qts *qts);
void			ft_qt_line(char *line, t_qts *qts, int *i);
void			ft_qt_start(char *line, t_qts *qts);
int				ft_backslash_check(char *line, int i);
char			*ft_find_case_cmd(char *cmd);

/*
** parsing functions, command specific functions.
*/

void			minishell_parser(char *line, t_shell *shell);
int				ft_echo_parser(char *line, int *i, t_shell *shell);
void			ft_cd(char *str, int *i, t_shell *shell);
void			ft_pwd_main(char *str, int *i, t_shell *shell);
void			ft_rd_parser(char *str, int *i, t_shell *shell);
void			ft_env_parser(char *str, int *i, t_shell *shell);
void			ft_execv_parser(char *cmd, char *str, int *i, t_shell *shell);
char			*ft_pwd(void);
void			exit_minishell(char *str, int *i, t_shell *shell);

/*
** execve/execute functions
*/

char			**ft_path_array(char *str, char *cmd);
void			ft_execute(char *cmd, char *str, char end, t_shell *shell);
int				ft_execve(char **argv, t_shell *shell);

/*
** export
*/
void			ft_export_parser(char *str, int *i, t_shell *shell);
int				ft_export(char *str, t_shell *shell);
int				*ft_order_env(char **env);
void			ft_sort_env(int *order, char **env, int start);
char			*ft_parse_env_str(int *order, char **env);
char			*ft_add_quotations(char *str, int start);
void			ft_update_env(t_shell *shell, char *str);
int				ft_valid_envvar(char *str);
char			*ft_find_varname(char *str);

/*
** unset
*/

void			ft_unset_parser(char *str, int *i, t_shell *shell);
void			ft_unset(char *str, t_shell *shell);

/*
** env
*/

int				env_main(char *str, t_shell *shell);
void			ft_add_env_back(t_shell *shell, char *input);
int				ft_envlen(t_shell *shell);
char			*ft_find_variable(char *str, int *i, t_shell *shell);
char			*ft_find_envvar(char *var, t_shell *shell);

/*
** clear shell struct
*/
void			ft_clear_shell(t_shell *shell);
#endif