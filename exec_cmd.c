
#include "minishell.h"

void	ensure_path_variable(t_data *data)
{
	t_env	*cur;
	t_env	*new_env;

	cur = data->env;
	while (cur)
	{
		if (strcmp(cur->key, "PATH") == 0)
			return ;
		cur = cur->next;
	}
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		ft_clear_garbage(data, 1);
	new_env->key = strdup("PATH");
	new_env->value = strdup("/usr/bin:/bin");
	new_env->next = data->env;
	data->env = new_env;
}

int	ft_strjoin_with_slash(char *dest, char *str, char *env, int *index)
{
	int	i;
	int	j;

	i = 0;
	while (*index < (PATH_MAX - 1) && env[*index] && env[*index] != ':')
		dest[i++] = env[(*index)++];
	(*index)++;
	dest[i++] = '/';
	j = 0;
	while (j < (PATH_MAX - 1) && str[j])
		dest[i++] = str[j++];
	dest[i] = '\0';
	return (0);
}

char	*find_cmd(t_data *data, char *sample)
{
	char	*paths;
	char	path[PATH_MAX];
	int		i;
	int		len;

	paths = extract_paths(data->env, len_env_list(data->env));
	if (!paths || ft_strlen(sample) > PATH_MAX / 2)
		return (display_cmd_not_found(sample));
	i = 0;
	len = ft_strlen(paths);
	while (i < len)
	{
		ft_strjoin_with_slash(path, sample, paths, &i);
		if (access(path, F_OK) == 0)
		{
			sample = ft_strdup(path);
			if (!sample)
			{
				print_error("Memory allocation failed");
				data->exit = -1;
			}
			return (sample);
		}
	}
	return (display_cmd_not_found(sample));
}

void	absolute_path(char **path, char *cmd, t_data *data)
{
	*path = ft_strdup(cmd);
	if (!(*path))
	{
		print_error("Memory allocation failed\n");
		ft_clear_garbage(data, 1);
	}
	if (access((*path), F_OK) != 0)
	{
		write(2, (*path), ft_strlen(*path));
		write(2, " : command not found\n", 21);
		free(*path);
		*path = NULL;
	}
}

int	is_regular_file(char **path, char *cmd, t_data *data)
{
	struct stat	path_stat;

	stat(*path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		print_error(cmd);
		print_error(" : Is a directory\n");
		data->exit = 126;
		return (0);
	}
	return (1);
}
