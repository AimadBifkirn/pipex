/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:20:31 by abifkirn          #+#    #+#             */
/*   Updated: 2025/01/18 12:59:56 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	countwords(char const *s, char c)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void	table_free(char **table, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(table[i]);
		i++;
	}
	free(table);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	size_t			max_len;

	max_len = ft_strlen(s) - start;
	if (len > max_len)
		len = max_len;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	ft_memcpy(res, s + start, len);
	res[len] = '\0';
	return (res);
}

static char	**alloc(char const *s, char c, char **table)
{
	size_t			j;
	unsigned int	i;
	int				x;

	i = 0;
	x = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (s[i + j] != c && s[i + j] != '\0')
			j++;
		if (j > 0)
		{
			table[x] = ft_substr(s, i, j);
			if (table[x++] == NULL)
			{
				table_free(table, x);
				return (NULL);
			}
			i = j + i - 1;
		}
		i++;
	}
	table[x] = NULL;
	return (table);
}

char	**ft_split(char *s, char c)
{
	char	**table;
	int		count;

	if (s == NULL)
		return (NULL);
	count = countwords(s, c);
	table = (char **)malloc(sizeof(char *) * (count + 1));
	if (table == NULL)
		return (NULL);
	if (alloc(s, c, table) == NULL)
		return (NULL);
	return (table);
}
