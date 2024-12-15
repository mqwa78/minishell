/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:49:39 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/14 16:10:36 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_env_var(t_env **env, char *key, char *value)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			if (!current->value)
			{
				print_error("Memory allocation failed\n");
				return (1);
			}
			return (0);
		}
		current = current->next;
	}
	if (!ft_create_elem1(env, ft_strdup(key), ft_strdup(value)))
		return (1);
	return (0);
}

int	ft_update_pwd(t_data *data)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		print_error("Error getting current working directory\n");
		return (1);
	}
	return (ft_set_env_var(&data->env, "PWD", cwd));
}

int	ft_update_oldpwd(t_data *data)
{
	char	cwd[1024];
	char	*current_pwd;

	current_pwd = getcwd(cwd, sizeof(cwd));
	if (current_pwd == NULL)
	{
		print_error("Error getting current working directory\n");
		while (current_pwd == NULL)
		{
			chdir("..");
			current_pwd = getcwd(cwd, sizeof(cwd));
		}
		return (1);
	}
	return (ft_set_env_var(&data->env, "OLDPWD", cwd));
}

int	ft_cd_home(t_data *data)
{
	char	*home;

	home = ft_get_value1(data, "HOME");
	if (!home)
	{
		print_error("HOME not set\n");
		return (1);
	}
	if (ft_update_oldpwd(data) != 0)
	{
		return (1);
	}
	if (chdir(home) != 0)
	{
		print_error("Error changing directory\n");
		free(home);
		return (1);
	}
	free(home);
	return (ft_update_pwd(data));
}

int	ft_cd(t_data *data, char **args)
{
	if (args[1] && args[2])
	{
		print_error("minishell: cd : too many arguments\n");
		return (1);
	}
	if (ft_update_oldpwd(data) != 0)
		return (1);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		return (ft_cd_home(data));
	else if (chdir(args[1]) != 0)
	{
		print_error("minishell: cd : no such file or directory\n");
		return (1);
	}
	return (ft_update_pwd(data));
}
