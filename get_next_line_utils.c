/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:48:41 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/05/19 19:30:16 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *ptr, size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	s = ptr;
	while (i < size)
	{
		s[i] = 0;
		i++;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int		gnl_strmove(char *dest, char *src, size_t num)
{
	unsigned char	*dst;
	unsigned char	*s;
	size_t			i;

	if ((dest == 0 && src == 0) || num == 0)
		return (0);
	dst = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (dest <= src)
	{
		while (i < num)
		{
			dst[i] = s[i];
			i++;
		}
	}
	else
		while (num--)
			dst[num] = s[num];
	return (1);
}

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = -1;
	if (str == 0)
		return (0);
	while (str[++i])
		if (str[i] == c)
			return (str + i);
	if (str[i] == 0 && c == 0)
		return (str + i);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*str;

	i = -1;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (str == 0)
		return (0);
	while (s1 && s1[++i])
		str[i] = s1[i];
	i = -1;
	while (s2 && s2[++i])
		str[len1 + i] = s2[i];
	str[len1 + i] = 0;
	free((char *)s1);
	return (str);
}
