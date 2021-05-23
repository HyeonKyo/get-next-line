/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:49:32 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/05/23 16:13:51 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>

void	ft_bzero(void *ptr, size_t size);
size_t	ft_strlen(const char *str);
int		gnl_strmove(char *dest, char *src, size_t num);
void	gnl_strcpy(char *dest, char *src, size_t size);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char const *s1, char const *s2);
int		clean(int fd, char *buf, char **backup, int n);
int		gnl_get_one_line(int fd, char **line, char **backup, char *buf);
int		get_next_line(int fd, char **line);

#endif
