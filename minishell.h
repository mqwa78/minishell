
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

typedef struct s_cmd
{	
	int				in;
	int				out;
	char			**cmd;
	struct s_cmd	*next;
}				t_cmd;
typedef struct s_data
{
	t_env	*env;
	t_tok	*tok;
	t_cmd	*cmd;
	char	*line;
	int		dollar;
}				t_data;

//		INITIALISATION DATA ET ENV		//

void	ft_init_data(t_data *data);
int		ft_setup_env(t_data *data, char **env);
int		ft_add_env(t_env **begin, char *str, char *key);
char	*ft_cpy_key(char *str);
char	*ft_cpy_value(char *str);

//		PARSE							//

int		ft_parse(t_data *data);
int		ft_open_quotes(char *s);
void	ft_quote(char c, int *dq, int *sq);
int		ft_invalid_char(char *s);
int		ft_check_spe(char *s, char c, int i);
int		ft_check_syntax(char *s);
int		ft_print_error_syn(char c);
int		ft_print_parse(t_data *data, int flag);

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

//		EXPANDER						//

void	expander(t_data *data);
void	ft_expand(t_data *data, t_tok **tok);
char	*ft_expand_word(t_data *data, char *s, int i);
char	*ft_get_key(t_data *data, char *s, int i);
char	*ft_get_value(t_data *data, char *key);
void	ft_clear_quote(t_data *data, t_tok **tok);

//		MANIPULATION LIST				//

int		ft_create_elem(t_env **begin, char *str, char *key);
int		ft_lstadd_back(t_env **lst, t_env *new);

//		BUILTINS						//

int		ft_echo(char **arg, int fd);
int		ft_pwd(void);
int		ft_env(t_env *env, int fd);

//		BUILTINS_UTILS					//

int		ft_check_n(char *str);

//		CLEAR FREE						//

void	ft_clear_garbage(t_data *data, int flag);
void	ft_clear_expand(t_data *data, char *key, char *value, int flag);
void	ft_clear_env(t_env **lst);
void	ft_clear_tok(t_tok **lst);

//		LIBFT							//

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_isspace(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);

//		DEBUG							//
void	ft_print_lst(t_tok *tok);
void	ft_print_lst2(t_env *tok);
#endif