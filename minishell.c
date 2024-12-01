
#include "minishell.h"

void	ft_init_data(t_data *data)
{
	data->env = NULL;
	data->tok = NULL;
	data->cmd = NULL;
	//data->line = ft_strdup("echo \"$? + $?\"");
	data->line = ft_strdup("echo bonjour yo yta gf rz fkz $HOME $USER $po");
	//data->line = ft_strdup("echo $HOME < bla $ $? \'$HOME\' | ls \"-l double quote \" | cat yo < file > toto    ");
	data->exit = 0;
}

int	minishell(char **env)
{
	t_data	data;

	ft_init_data(&data);
	if (!ft_setup_env(&data, env))
		return (1);
	// debut boucle infini
	printf("%s\n", data.line);
	//data.line = ft_readline + strdup pour malloc
	//if !data.line
	//ft_clear_env(&data.env);
	//return (1);
	if (!ft_parse(&data))
	{
		//on va utiliser continue pour relire une line
		return (1);
	}
	if (!executer(&data))
	{
		ft_clear_cmd(&data.cmd);
		ft_clear_env(&data.env);
		printf("malloc error\n");
		return (1);
	}
	//ft_print_lst4(data.cmd);
	ft_clear_env(&data.env);
	ft_clear_cmd(&data.cmd);
	return (0);
}