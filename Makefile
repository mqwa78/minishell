SRC	=	./src/built_cd.c
SRC	+=	./src/built_echo.c
SRC	+=	./src/built_env.c
SRC	+=	./src/built_exit.c
SRC	+=	./src/built_export.c
SRC	+=	./src/built_pwd.c
SRC	+=	./src/built_unset.c
SRC	+=	./src/clear_all.c
SRC	+=	./src/clear_cmd.c
SRC	+=	./src/clear_list.c
SRC	+=	./src/cmd_builder.c
SRC	+=	./src/cmd_fd.c
SRC	+=	./src/cmd_tools.c
SRC	+=	./src/env_setup.c
SRC	+=	./src/env_tools.c
SRC	+=	./src/env_tools2.c
SRC	+=	./src/exec_built.c
SRC	+=	./src/exec_cmd.c
SRC	+=	./src/exec_exist.c
SRC	+=	./src/exec_tools.c
SRC	+=	./src/executer.c
SRC	+=	./src/expander_ambi.c
SRC	+=	./src/expander_lst.c
SRC	+=	./src/expander_quotes.c
SRC	+=	./src/expander_tools.c
SRC	+=	./src/expander.c
SRC	+=	./src/ft_isalnum.c
SRC	+=	./src/ft_isalpha.c
SRC	+=	./src/ft_isdigit.c
SRC	+=	./src/ft_isoperator.c
SRC	+=	./src/ft_isspace.c
SRC	+=	./src/ft_itoa.c
SRC	+=	./src/ft_memset.c
SRC	+=	./src/ft_lst_to_array.c
SRC	+=	./src/ft_putchar_fd.c
SRC	+=	./src/ft_alt_putchar.c
SRC	+=	./src/ft_putendl_fd.c
SRC	+=	./src/ft_putstr_fd.c
SRC	+=	./src/ft_strchr.c
SRC	+=	./src/ft_strcmp.c
SRC	+=	./src/ft_strdup.c
SRC	+=	./src/ft_strlen.c
SRC	+=	./src/ft_strncmp.c
SRC	+=	./src/here_clear.c
SRC	+=	./src/here_quote.c
SRC	+=	./src/heredoc.c
SRC	+=	./src/main.c
SRC	+=	./src/minishell.c
SRC	+=	./src/parse_print.c
SRC	+=	./src/parse.c
SRC	+=	./src/signals.c
SRC	+=	./src/signals2.c
SRC	+=	./src/signals3.c
SRC	+=	./src/token_synthax.c
SRC	+=	./src/token_tools.c
SRC	+=	./src/tokeniser.c
OBJ	=	$(SRC:.c=.o)
NAME	=	minishell
CC	=	cc	
CFLAGS	= -Wall -Wextra -Werror
CFLAGS += -I./include/

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(OBJ) $(CFLAGS) -lreadline -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)


re : fclean all

.PHONY : all clean fclean re