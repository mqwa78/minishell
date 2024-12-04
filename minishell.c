
#include "minishell.h"

void	ft_init_data(t_data *data)
{
	data->env = NULL;
	data->tok = NULL;
	data->cmd = NULL;
	data->line = NULL;
	//data->line = ft_strdup("echo \"$? + $?\"");
	//data->line = ft_strdup("echo $HOME < bla $ $? \'$HOME\' | ls \"-l double quote \" | cat yo < file > toto    ");
	data->exit = 0;
}

int	minishell(char **env)
{
	t_data	data;
	int	i;

	ft_init_data(&data);
	if (!ft_setup_env(&data, env))
		return (1);
	i = 0;
	while (i++ < 6)
	{
		if (i % 6 == 1)
			data.line = ft_strdup("unset PWD");
		else if (i % 6 == 2)
			data.line = ft_strdup("pwd");
		else if (i % 6 == 3)
			data.line = ft_strdup("cd ..");
		else if (i % 6 == 4)
			data.line = ft_strdup("pwd");
		else if (i % 6 == 5)
			data.line = ft_strdup("cd ..");
		else if (i % 6 == 0)
			data.line = ft_strdup("echo $$$");
	if (!data.line)
		return (1);
	printf("CMD NUMERO %d -------------------\n", i - 1);
	//printf("%s\n", data.line);
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
	printf("%d\n", data.exit);
	ft_clear_cmd(&data.cmd);
	}
	ft_clear_env(&data.env);
	return (0);
}