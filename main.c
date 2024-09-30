
#include "minishell.h"

void	ft_init_data(t_data *data)
{
	data->env = NULL;
	data->tok = NULL;
}

/*int	main(int ac, char **av, char **env)
{	
	t_data	data;
	//t_env	*cur;

	(void) ac;
	(void) av;
	ft_init_data(&data);
	if (!ft_setup_env(&data, env))
		return (0);
	//cur = data.env;
	ft_env(data.env, 1);
	ft_clear_env(&data.env);
	return (0);
}*/