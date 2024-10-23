
#include "minishell.h"

void	ft_print_lst(t_tok *tok)
{
	t_tok	*cur;

	cur = tok;
	while (cur->next)
	{
		printf("%s\n", cur->token);
		printf("%d\n", cur->type);
		cur = cur->next;
	}
	printf("%s\n", cur->token);
	printf("%d\n", cur->type);
	while (cur)
	{
		printf("%s\n", cur->token);
		cur = cur->prev;
	}
}

void	ft_init_data(t_data *data)
{
	data->env = NULL;
	data->tok = NULL;
	data->line = ft_strdup("echo \"$HOME$ $? $USER\" >> file.txt | $YO << $USER |");
	data->spe = 0;
}

int	main(int ac, char **av, char **env)
{	
	t_data	data;

	(void) ac;
	(void) av;
	ft_init_data(&data);
	if (!ft_setup_env(&data, env))
		return (0);
	//data.line = ft_readline + strtrim pour les espaces
	if (!ft_parse(&data))
	{
		//on va utiliser continu pour relire une line
		return (0);
	}
	//printf("%s\n", data.line);
	ft_print_lst(data.tok);
	ft_clear_env(&data.env);
	ft_clear_tok(&data.tok);
	return (0);
}