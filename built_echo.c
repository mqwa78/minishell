
#include "minishell.h"

int	ft_check_n(char *str)
{	
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] && str[i] != '-')
		return (0);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	ft_echo(char **arg, int fd)
{
	int	i;
	int	n_op;

	if (!arg || !arg[0])
		return (1);
	if (!arg[1])
	{
		ft_putchar_fd('\n', fd);
		return (1);
	}
	i = 1;
	n_op = ft_check_n(arg[i]);
	if (n_op)
		i++;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], fd);
		if (arg[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (n_op)
		return (0);
	ft_putchar_fd('\n', fd);
	return (0);
}
