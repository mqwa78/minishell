
#include "minishell.h"

void	ft_print_lst(t_tok *tok)
{
	t_tok	*cur;

	cur = tok;
	while (cur)
	{
		printf("%s\n", cur->token);
		printf("%d\n", cur->type);
		cur = cur->next;
	}
}

void	ft_print_lst4(t_cmd *tok)
{
	t_cmd	*cur;
	int		i;

	cur = tok;
	while (cur)
	{
		i = 0;
		printf("Elem : %d\n\n", i + 1);
		while (cur->tab[i])
		{
			printf("%s\n", cur->tab[i]);
			i++;
		}
		cur = cur->next;
		printf("\n");
	}
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	return (minishell(env));
}
