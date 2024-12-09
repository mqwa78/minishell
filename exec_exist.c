
#include "minishell.h"

int	command_exists(char **path, t_data *data, char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		*path = find_cmd(data, cmd);
	else
		absolute_path(path, cmd, data);
	if (!(*path) && data->exit == -1)
		ft_clear_garbage(data, 1);
	if (!(*path))
	{
		data->exit = 127;
		return (0);
	}
	if (access((*path), X_OK) != 0)
	{
		perror(*path);
		free((*path));
		(*path) = NULL;
		data->exit = 126;
		return (0);
	}
	if (!is_regular_file(path, cmd, data))
		return (0);
	return (1);
}