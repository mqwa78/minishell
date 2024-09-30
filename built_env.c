
#include "minishell.h"

int	ft_env(t_env *env, int fd)
{
	t_env	*cur;

	cur = env;
	if (!cur)
		return (1);
	while (cur != NULL)
	{
		ft_putstr_fd(cur->key, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(cur->value, fd);
		ft_putchar_fd('\n', fd);
		cur = cur->next;
	}
	return (0);
}