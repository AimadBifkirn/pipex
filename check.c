/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:20:35 by abifkirn          #+#    #+#             */
/*   Updated: 2025/01/25 13:35:54 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t			size1;
	size_t			size2;
	char			*res;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	res = (char *)malloc(size1 + size2 + 1);
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s1, size1);
	ft_memcpy(res + size1, s2, size2);
	res[size1 + size2] = '\0';
	return (res);
}

char	*check_command(char **parts_path, char **s_cmd)
{
	int		i;
	char	*joined;
	char	*tmp;

	i = 0;
	while (parts_path[i] != NULL)
	{
		tmp = ft_strjoin(parts_path[i], "/");
		joined = ft_strjoin(tmp, s_cmd[0]);
		free(tmp);
		tmp = NULL;
		if (access(joined, F_OK) == 0)
			return (joined);
		free(joined);
		i++;
	}
	free_all(parts_path);
	print_error(": command not found", s_cmd[0]);
	free_all(s_cmd);
	exit(127);
}

int	help_helper(char *str, char *path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!path)
	{
		while (str[i])
		{
			if (str[i] == '/')
				j++;
			i++;
		}
		if (j == 0)
			return (1);
	}
	return (0);
}
