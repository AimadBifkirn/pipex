/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:20:40 by abifkirn          #+#    #+#             */
/*   Updated: 2025/01/25 11:01:33 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *s);
void	free_all(char **table);
char	*get_path(char **env);
char	*check_command(char **parts_path, char **s_cmd);
int		exec_command(char *cmd, char **env);
void	print_error(char *str, char *cmd);
int		help_helper(char *str, char *path);

#endif
