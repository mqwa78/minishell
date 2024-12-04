
#include "minishell.h"

int	ft_print_export_error(char *str)
{
	ft_putstr_fd("Minishell : export : ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(" : not a valid identifier\n", 2);
	return (1);
}

int	ft_print_export(t_env *env)
{
	t_env	*cur;

	cur = env;
	if (!cur)
		return (1);
	while (cur)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(cur->key, 1);
		ft_putchar_fd('=', 1);
		ft_putchar_fd('\"', 1);
		ft_putstr_fd(cur->value, 1);
		ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		cur = cur->next;
	}
	return (0);
}

int	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (0);
}

int	ft_print_parse(t_data *data, int flag)
{	
	if (flag == 1)
		write(2, "minishell : error open quotes\n", 31);
	else if (flag == 2)
		write(2, "minishell : error invalid char\n", 32);
	free(data->line);
	return (0);
}
