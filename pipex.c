/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:20:12 by abifkirn          #+#    #+#             */
/*   Updated: 2025/01/25 10:35:25 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	fonction_child(int *p, char **argv, char	**env)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		print_error(": no such file or directory", argv[1]);
		exit(EXIT_FAILURE);
	}
	dup2 (fd, 0);
	dup2 (p[1], 1);
	close (p[0]);
	close(p[1]);
	close(fd);
	if (exec_command(argv[2], env) == 1)
	{
		print_error (": command not found", argv[2]);
		exit (127);
	}
	return (0);
}

static int	fonction_child2(int *p, char **argv, char	**env)
{
	int	fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2 (fd, 1);
	dup2 (p[0], 0);
	close (p[1]);
	close(p[0]);
	close(fd);
	if (exec_command(argv[3], env) == 1)
	{
		print_error (": command not found", argv[3]);
		exit (127);
	}
	return (0);
}

static void	call_child(int i1, int *d, char **argv, char **env)
{
	if (i1 == -1)
	{
		perror("CALL_CHILD");
		exit(EXIT_FAILURE);
	}
	else if (i1 == 0)
		fonction_child(d, argv, env);
}

static void	call_child2(int i2, int *d, char **argv, char **env)
{
	if (i2 == -1)
	{
		perror("CALL_FATHER");
		exit(EXIT_FAILURE);
	}
	else if (i2 == 0)
		fonction_child2(d, argv, env);
}

int	main(int argc, char **argv, char **env)
{
	int		d[2];
	pid_t	i1;
	pid_t	i2;
	int		status;

	if (argc == 5)
	{
		if (pipe(d) == -1)
			exit(EXIT_FAILURE);
		i1 = fork();
		call_child(i1, d, argv, env);
		i2 = fork();
		call_child2(i2, d, argv, env);
		close(d[0]);
		close(d[1]);
		waitpid(i1, NULL, 0);
		waitpid(i2, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (1);
	}
	perror("syntax : infile <command> <command> outfile");
	return (1);
}
