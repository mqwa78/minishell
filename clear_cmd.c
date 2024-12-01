
#include "minishell.h"

void	ft_clear_tab2(char **tab, int i)
{
	if (!tab || !tab[0])
		return ;
	while (--i >= 0)
		free(tab[i]);
	free(tab);
}

int	ft_free_elem(t_cmd **elem, char **tab, int i, int flag)
{
	if (flag)
		ft_clear_tab2(tab, i);
	free(elem);
	return (0);
}

void	ft_clear_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_clear_cmd(t_cmd **lst)
{
	if (!lst || !(*lst))
		return ;
	ft_clear_cmd(&(*lst)->next);
	ft_clear_tab((*lst)->tab);
	if ((*lst)->in >= 0)
		close((*lst)->in);
	if ((*lst)->out >= 0)
		close((*lst)->out);
	free(*lst);
	*lst = NULL;
}

void	ft_clear_builder(t_data *data, t_cmd **cmd)
{
	ft_clear_cmd(cmd);
	ft_clear_garbage(data, -1);
}