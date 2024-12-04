
#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <linux/limits.h>

# define INPUT		1	// "<"
# define HEREDOC	2	// "<<"
# define TRUNC		3	// ">"
# define APPEND		4	// ">>"
# define PIPE		5	// "|"
# define FILE		6	// "File"
# define CMD		7	// "Command"
# define ARG		8	// "Argument"
# define SPE_SIZE	2

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
	char			**tab;
	struct s_cmd	*next;
}				t_cmd;
typedef struct s_data
{
	t_env	*env;
	t_tok	*tok;
	t_cmd	*cmd;
	char	*line;
	int		exit;
}				t_data;

//		INITIALISATION DATA ET ENV		//

int		minishell(char **env);
void	ft_init_data(t_data *data);
int		ft_setup_env(t_data *data, char **env);
int		ft_add_env(t_env **begin, char *str, char *key);
char	*ft_cpy_key(char *str);
char	*ft_cpy_value(char *str, char *key);
char	*ft_get_value1(t_data *data, char *key);

//		PARSE							//

int		ft_parse(t_data *data);
int		ft_only_spaces(char *s);
int		ft_open_quotes(char *s);
void	ft_quote(char c, int *dq, int *sq);
int		ft_invalid_char(char *s);

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

//		CMD_BUILDER						//

int		cmd_builder(t_data *data);
int		ft_create_cmd(t_data *data, t_cmd **cmd, t_tok *tok);
int		ft_new_cmd(t_cmd **begin);
int		ft_lstadd_back4(t_cmd **lst, t_cmd *new);
int		ft_fill_cmd(t_cmd **elem, t_tok *tok);
int		ft_fill_tab(t_cmd **elem, t_tok *tok);
int		ft_count_tokens(t_tok *tok);

//		EXECUTOR						//

int		executer(t_data *data);
char	**ft_lst_to_array(t_data *data);
int		ft_count_env_elem(t_env *env);
char	*ft_fill_env(t_env *env);
int		is_built(char *cmd);
int		lunch_built(t_data *data, t_cmd *cmd);

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

//		PRINT							//

int		ft_print_parse(t_data *data, int flag);
int		print_error(char *str);
int		ft_print_export_error(char *str);
int		ft_print_export(t_env *env);

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

//		LIBFT							//

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_itoa(int n);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);

//		DEBUG							//
void	ft_print_lst(t_tok *tok);
void	ft_print_lst2(t_env *tok);
void	ft_print_lst3(t_exp *tok);
void	ft_print_lst4(t_cmd *tok);
#endif