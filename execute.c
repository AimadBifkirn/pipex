/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:20:23 by abifkirn          #+#    #+#             */
/*   Updated: 2025/01/25 13:39:47 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(char **table)
{
	int	i;

	i = 0;
	while (table[i] != NULL)
	{
		free(table[i]);
		table[i] = NULL;
		i++;
	}
	free(table);
	table = NULL;
}

char	*get_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = "PATH=";
	while (*env)
	{
		while ((*env)[i] && (*env)[i] == path[i])
			i++;
		if (i == 5)
			return (*env + 5);
		i = 0;
		env++;
	}
	return (NULL);
}

static void	exec_helper(char **s_cmd, char **env, char **file_p)
{
	char	*path;
	char	**parts_path;

	path = get_path(env);
	if (path)
	{
		parts_path = ft_split(path, ':');
		if (!parts_path)
		{
			free_all(s_cmd);
			perror("error spliting the path");
			exit(127);
		}
		*file_p = check_command(parts_path, s_cmd);
		free_all(parts_path);
	}
	else if (!path)
	{
		if (help_helper(s_cmd[0], path) == 1)
			*file_p = ft_strjoin("", "");
		else
			*file_p = s_cmd[0];
	}
}

void	print_error(char *str, char *cmd)
{
	write (2, cmd, ft_strlen(cmd));
	write (2, str, ft_strlen(str));
	write (2, "\n", 1);
}

int	exec_command(char *cmd, char **env)
{
	char	**s_cmd;
	char	*file_p;

	s_cmd = ft_split(cmd, ' ');
	if (s_cmd[0] == NULL)
	{
		free_all(s_cmd);
		return (1);
	}
	file_p = NULL;
	exec_helper(s_cmd, env, &file_p);
	if (execve (file_p, s_cmd, env) == -1)
	{
		if (file_p == cmd)
			free_all(s_cmd);
		else
		{
			free_all(s_cmd);
			free(file_p);
			file_p = NULL;
		}
		return (1);
	}
	return (0);
}
