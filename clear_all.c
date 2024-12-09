
#include "minishell.h"

void	ft_close_herited_fd(void)
{
	close(1);
	close(20);
	close(19);
	close(2);
	close(0);
}

void	ft_clear_all(t_data *data, char *str, int err)
{
	if (data->cmd)
		ft_clear_cmd(&data->cmd);
	if (data->env)
		ft_clear_env(&data->env);
	if (data->pip[0] && data->pip[0] != -1)
		close(data->pip[0]);
	if (data->pip[1] && data->pip[1] != -1)
		close(data->pip[1]);
	if (str)
		ft_putstr_fd(str, 2);
	ft_close_herited_fd();
	exit(err);
}