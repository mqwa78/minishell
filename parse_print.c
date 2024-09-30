
#include "minishell.h"

int	ft_print_error_syn(char c)
{
	write(2, "Minishell : syntax error near unexpected token ", 48);
	write(2, "\'", 1);
	write(2, &c, 1);
	write(2, "\'", 1);
	write(2, "\n", 1);
	return (1);
}

int	ft_print_parse(int flag)
{	
	if (flag == 1)
		write(2, "minishell : error open quotes\n", 31);
	else if (flag == 2)
		write(2, "minishell : error invalid char\n", 32);
	return (0);
}