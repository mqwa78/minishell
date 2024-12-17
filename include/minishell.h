/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:42:54 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/17 19:14:47 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <linux/limits.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define INPUT		1	// "<"
# define HEREDOC	2	// "<<"
# define TRUNC		3	// ">"
# define APPEND		4	// ">>"
# define PIPE		5	// "|"
# define FILE		6	// "File"
# define CMD		7	// "Command"
# define ARG		8	// "Argument"
# define SPE_SIZE	2
# define HERENAME	".heredoc42.mq.tmp"

extern pid_t	g_sig_pid;
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_tok
{
	int				type;
	char			*token;
	struct s_tok	*prev;
	struct s_tok	*next;
}				t_tok;

typedef struct s_exp
{
	int				sq;
	struct s_exp	*prev;
	struct s_exp	*next;
}				t_exp;
typedef struct s_cmd
{	
	int				in;
	int				out;
	int				skip;
	int				nocmd;
	char			**tab;
	struct s_cmd	*next;
}				t_cmd;
typedef struct s_data
{
	t_env	*env;
	t_env	*dup;
	t_tok	*tok;
	t_cmd	*cmd;
	char	*line;
	int		pip[2];
	int		exit;
}				t_data;

//		INITIALISATION DATA ET ENV		//

int		minishell(char **env);
void	ft_init_data(t_data *data);
int		ft_setup_env(t_data *data, char **env);
int		ft_add_env(t_env **begin, char *str, char *key);
char	*ft_cpy_key(char *str);
char	*ft_cpy_key2(char *str);
char	*ft_cpy_value(char *str, char *key);
char	*ft_cpy_value2(char *str, char *key);
char	*ft_get_value1(t_data *data, char *key);
void	ft_dup_env(t_data *data, t_env *env);
int		ft_get_pos(char *key, t_env *env);
void	setup_signal_handlers(int sig);

//		PARSE							//

int		ft_parse(t_data *data);
int		ft_only_spaces(char *s);
int		ft_open_quotes(char *s);
void	ft_quote(char c, int *dq, int *sq);
void	print_exit_error(t_data *data, char *arg);

//		TOKENISER						//

int		tokeniser(t_data *data, char *s);
int		ft_add_token(t_tok **tok, char *s, int *i);
int		ft_count_len(char *s, int i);
int		ft_create_token(t_tok **begin, char *str, int type);
int		ft_lstadd_back2(t_tok **lst, t_tok *new);
int		ft_new_token(t_tok **begin, char *str, int type);
int		is_special(char *s, char c, int i);
int		ft_add_special(t_tok **tok, char *s, int *i);
int		ft_create_spe(t_tok **begin, char *str, int type);
int		ft_check_synthax_token(t_tok *tok);
int		ft_check_pipe(t_tok *tok);
int		ft_check_spe_synthax(t_tok *tok);
void	ft_setup_token_types(t_tok *tok);

//		EXPANDER						//

void	expander(t_data *data);
void	ft_expand(t_data *data, t_tok **tok, t_exp **x);
char	*ft_expand_word(t_data *data, char *s, int i);
char	*ft_get_key(t_data *data, char *s, int i);
char	*ft_get_value(t_data *data, char *key);
char	*ft_free_and_return(char *new, char *old);
char	*ft_expand_spe(t_data *data, char *s, int i);
void	ft_clear_quote(t_data *data, t_tok **tok);
int		ft_count_quotes(char *s);
char	*ft_erase_quotes(char *s, int size);
void	ft_cpy_simple(char *s, char **new, int *i, int *j);
void	ft_cpy_double(char *s, char **new, int *i, int *j);
void	ft_cpy(char *s, char **new, int *i, int *j);
void	ft_create_lst_exp(t_data *data, t_exp **exp, char *s);
void	ft_add_elem_exp(t_data *data, t_exp **begin, int sq);
int		ft_new_exp(t_exp **begin, int sq);
int		ft_lstadd_back3(t_exp **lst, t_exp *new);
int		exp_q(t_exp **exp);
void	ft_reset_lst(t_exp **exp);
void	ft_check_ambiguous(t_data *data, t_tok *tok);

//		CMD_BUILDER						//

int		cmd_builder(t_data *data);
int		ft_create_cmd(t_data *data, t_cmd **cmd, t_tok *tok);
int		ft_new_cmd(t_cmd **begin);
int		ft_lstadd_back4(t_cmd **lst, t_cmd *new);
int		ft_fill_cmd(t_data *data, t_cmd **elem, t_tok *tok);
int		ft_fill_tab(t_cmd **elem, t_tok *tok);
int		ft_count_tokens(t_tok *tok);
int		open_file(t_data *data, char *filename, int type);
int		get_out(t_data *data, t_cmd **elem, t_tok *tok);
int		get_in(t_data *data, t_cmd **elem, t_tok *tok);
int		ft_get_files(t_data *data, t_cmd **elem, t_tok *token);
int		open_here(t_data *data, char *key);

//		EXECUTOR						//

int		executer(t_data *data);
int		ft_count_env_elem(t_env *env);
char	*ft_fill_env(t_env *env);
int		is_built(char *cmd);
void	exec_built(t_data *data, t_cmd *cmd, int out);
int		exec_cmd(t_data *data, t_cmd *cmd, int *pip);
void	child_process(t_data *data, t_cmd *cmd, int *pip);
void	parent_process(t_cmd *cmd, int *pip);
void	wait_all(t_data *data);
int		command_exists(char **path, t_data *data, char *cmd);
int		is_regular_file(char **path, char *cmd, t_data *data);
void	absolute_path(char **path, char *cmd, t_data *data);
char	*find_cmd(t_data *data, char *sample);
char	*display_cmd_not_found(const char *cmd);
int		len_env_list(t_env *lst);
char	*extract_paths(t_env *env_list, int len);
int		ft_strjoin_with_slash(char *dest, char *str, char *env, int *index);
void	ensure_path_variable(t_data *data);
void	ft_redirect(t_cmd *cmd, int *pip);
int		launch_builtin(t_data *data, t_cmd *cmd);
void	setup_built(int *pip, t_cmd *cmd, t_data *data);

//		MANIPULATION LIST				//

int		ft_create_elem(t_env **begin, char *str, char *key);
int		ft_create_elem1(t_env **begin, char *key, char *value);
int		ft_lstadd_back(t_env **lst, t_env *new);

//		BUILTINS						//

int		ft_echo(char **arg);
int		ft_pwd(void);
int		ft_env(t_env *env);
int		ft_unset(t_data *data, char **cmd);
int		ft_export(t_data *data, char **cmd);
int		ft_cd(t_data *data, char **args);
void	ft_exit(t_data *data, char **args);

//		PRINT							//

int		ft_print_parse(t_data *data, int flag);
int		print_error(char *str);
int		ft_print_export_error(char *str);
int		ft_print_export(t_env *env);
void	print_here(char *str, int fd, int flag);

//		CLEAR FREE						//

void	ft_clear_garbage(t_data *data, int flag);
void	ft_clear_expand(t_data *data, char *key, char *value, int flag);
void	ft_clear_env(t_env **lst);
void	ft_clear_tok(t_tok **lst);
void	ft_clear_exp(t_exp **lst);
void	ft_clear_cmd(t_cmd **lst);
void	ft_clear_builder(t_data *data, t_cmd **cmd);
void	ft_clear_tab(char **tab);
void	ft_clear_tab2(char **tab, int i);
int		ft_free_elem(t_cmd **elem, char **tab, int i, int flag);
void	ft_clear_all(t_data *data, char *str, int err);
void	ft_close_herited_fd(void);
void	ft_clear_all_env(t_data *data, t_env **list);
void	ft_clear_expand_here(t_data *data, char *key, char *value, int flag);
void	ft_clear_spe_here(t_data *data, char *str);

//		LIBFT							//

void	ft_putchar_fd(char c, int fd);
int		ft_alt_putchar(int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_itoa(int n);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_isoperator(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
char	**ft_lst_to_array(t_data *data);

//		SIGNAL							//

int		init_signals(t_data *data);
int		init_signals_alt(t_data *data);
#endif