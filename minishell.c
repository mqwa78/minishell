
#include "minishell.h"

pid_t	g_sig_pid;

void	ft_init_data(t_data *data)
{
	data->env = NULL;
	data->tok = NULL;
	data->cmd = NULL;
	data->line = NULL;
	data->pip[0] = -1;
	data->pip[1] = -1;
	data->exit = 0;
	g_sig_pid = 0;
}

int	minishell(char **env)
{
	t_data	data;
	int	i;

	ft_init_data(&data);
	if (!ft_setup_env(&data, env))
		return (1);
	i = 0;
	while (i++ < 3)
	{
		if (i % 3 == 1)
			data.line = ft_strdup("grepp");
		else if (i % 3 == 2)
			data.line = ft_strdup("echo $?");
		else if (i % 3 == 0)
			data.line = ft_strdup("echo $?");
		/*else if (i % 6 == 4)
			data.line = ft_strdup("ls | ls | cat");
		else if (i % 6 == 5)
			data.line = ft_strdup("grep");
		else if (i % 6 == 0)
			data.line = ft_strdup("ls -l | wc -c | echo $?");*/
	if (!data.line)
		return (1);
	printf("CMD NUMERO %d -------------------\n", i - 1);
	printf("%s\n", data.line);
	//data.line = ft_readline + strdup pour malloc
	//if !data.line
	//ft_clear_env(&data.env);
	//return (1);
	if (!ft_parse(&data))
		continue ;
	if (!executer(&data))
	{
		ft_clear_cmd(&data.cmd);
		ft_clear_env(&data.env);
		printf("malloc error\n");
		return (1);
	}
	//printf("%d\n", data.exit);
	ft_print_lst4(data.cmd);
	ft_clear_cmd(&data.cmd);
	}
	ft_clear_env(&data.env);
	ft_close_herited_fd();
	return (0);
}