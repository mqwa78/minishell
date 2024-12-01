
#include "minishell.h"

int	ft_env(t_env *env)
{
	t_env	*cur;

	cur = env;
	if (!cur)
		return (1);
	while (cur != NULL)
	{
		ft_putstr_fd(cur->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(cur->value, 1);
		ft_putchar_fd('\n', 1);
		cur = cur->next;
	}
	return (0);
}
