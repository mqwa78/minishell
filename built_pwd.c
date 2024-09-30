
#include "minishell.h"

int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX))
	{
		ft_putendl_fd(path, 1);
		return (0);
	}
	else
		return (1);
}
