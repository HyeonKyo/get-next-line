/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:49:32 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/05/19 15:58:08 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>

int		get_next_line(int fd, char **line);
void	ft_bzero(void *ptr, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strdup(char *src);
void	*ft_memmove(void *dest, const void *src, size_t num);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
