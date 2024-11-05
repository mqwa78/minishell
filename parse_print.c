
#include "minishell.h"

int	ft_print_parse(t_data *data, int flag)
{	
	if (flag == 1)
		write(2, "minishell : error open quotes\n", 31);
	else if (flag == 2)
		write(2, "minishell : error invalid char\n", 32);
	free(data->line);
	return (0);
}
