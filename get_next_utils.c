/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:48:41 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/05/18 16:37:24 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_lines.h"

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
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (src[i])
		i++;
	temp = (char *)malloc(sizeof(char) * (i + 1));
	if (temp == 0)
		return (0);
	while (++j <= i)
		temp[j] = src[j];
	return (temp);
}

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	char	*dst;
	char	*s;
	size_t	i;

	if ((dest == 0 && src == 0) || num == 0)
		return (dest);
	dst = dest;
	s = (char *)src;
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
	return (dest);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	if (src == 0)
		return (0);
	while (src[len])
		len++;
	while (i + 1 < size && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (size != 0)
		dest[i] = 0;
	return (len);
}

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = -1;
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
	while (s1[++i])
		str[i] = s1[i];
	i = -1;
	while (s2[++i])
		str[len1 + i] = s2[i];
	str[len1 + i] = 0;
	free((char *)s1);
	return (str);
}
