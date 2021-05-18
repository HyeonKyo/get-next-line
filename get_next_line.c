/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:48:09 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/05/18 16:37:32 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_lines.h"
#include <stdio.h>

int		get_next_line(int fd, char **line)
{
	ssize_t		n_bytes;
	int			flag;
	char		*buf;
	static char	*backup[OPEN_MAX + 1];
	char		*tmp;

	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)) || BUFFER_SIZE < 1
		|| fd < 0 || fd > OPEN_MAX || !(*line) || !buf)
		return (-1);
	while ((n_bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		flag = 1;
		//맨 처음 backup이 비어있는 경우
		if (!(backup[fd]))
		{
			backup[fd] = ft_strdup(buf);
			flag = 0;
		}
		//buf없이 backup에개행이 없으면 buf와 backup을 합쳐줌.
		if (!ft_strchr(backup[fd], '\n') && flag)
		{
			ft_strjoin(backup[fd], buf);
			flag = 0;
		}
		//다시 buf에 개행이 있다면 -> line에 할당하고 개행까지 복사해준 후 
		//backup의 개행 후를 처음으로 옮겨놓음.
		//그 후 buf를 해제하고 리턴
		if ((tmp = ft_strchr(backup[fd], '\n')))
		{
			tmp++;
			*line = (char *)malloc((tmp - backup[fd]) * sizeof(char));
			ft_strlcpy(*line, backup[fd], tmp - backup[fd]);
			ft_memmove(backup[fd], tmp, ft_strlen(tmp) + 1);
			//buf를 backup에 합치지 않은 상태라면 합쳐줌.
		}
		if (flag)
			ft_strjoin(backup[fd], buf);
		if (tmp)
		{
			free(buf);
			return (1);
		}
		//buf에 개행이 없는 경우 이므로 다시 읽기위해 buf를 비워줌.
		ft_bzero(buf, BUFFER_SIZE + 1);
	}
	if (n_bytes == 0)
	{
		if ((tmp = ft_strchr(backup[fd], '\n')))
		{
			tmp++;
			*line = (char *)malloc((tmp - backup[fd]) * sizeof(char));
			ft_strlcpy(*line, backup[fd], tmp - backup[fd]);
			free((char *)backup[fd]);
		}
		else
			*line = 0;
	}
	free(buf);
	return (n_bytes);
}

int main()
{
	char *line;
	int fd;
	int	n;

	fd = open("text.txt", O_RDONLY);
	while ((n = get_next_line(fd, &line)) >= 0)
	{
		printf("n : %d\n", n);
		printf("line : %s\n", line);
		printf("---------------------\n");
	}
	close(fd);

	return (0);
}

/*
 *  예외사항
 *  - EOF까지 읽어서 read의 리턴값이 0인 경우인데,
 *    마지막 읽은 문자열 사이에 또는 이전에 저장된 버퍼 내에 개행문자가 있는 경우?
 *    => 그럼 개행 전 문자열을 line에 넣고 그 이후 문자열은 출력이 안됨.
 *    => 어떻게 처리?
 *    - buffer_size만큼 읽었을 때 이전 문자열까지 합해도 개행이 없는 경우 line에 무엇을?
 *
 *  - get next line 함수가 중간에 에러나는 경우 그 동안 할당했던 메모리 다 해제하고 -1을 리턴?
 *
 *  - 함수 한 번에 무조건 BUFFER_SIZE만큼만 읽는 건지
 *    아니면 개행을 만날 때 까지 여러번의 BUFFER_SIZE만큼 읽는 건지? => 이게 맞는듯
 **/
