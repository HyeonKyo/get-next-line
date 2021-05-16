/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:48:09 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/05/15 17:05:25 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_lines.h"
#include <stdio.h>

int		get_next_line(int fd, char **line)
{
	ssize_t		n_bytes;
	int			flag;
	int			len;
	char		*buf;
	static char	*backup[FOPEN_MAX + 1];
	char		*tmp;

	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)) || BUFFER_SIZE < 1
		|| fd < 0 || fd > FOPEN_MAX || !*line || !buf)
		return (-1);
	while (n_bytes = read(fd, buf, BUFFER_SIZE) > 0)
	{
		if (!*backup[fd])
			backup[fd] = ft_strdup(buf);
		flag = 1;
		if (!(tmp = ft_strchr(backup[fd], '\n') + 1))
		{
			ft_strjoin(backup[fd], buf);
			flag = 0;
		}
		if (tmp = ft_strchr(backup[fd], '\n') + 1)
		{
			*line = (char *)malloc((tmp - backup[fd]) * sizeof(char));
			ft_strlcpy(*line, backup[fd], tmp - backup[fd]);
			len = tmp - backup[fd];
			ft_memmove(backup[fd], tmp, ft_strlen(tmp) + 1);
			if (flag)
				ft_strjoin(backup[fd], buf);
			free(buf);
			return (1);
		}
		ft_bzero(buf, BUFFER_SIZE + 1);
	}
	//n_bytes가 0일 경우 => 한 번의 작업 필요
	//-1인 경우 => 에러이므로 free후 -1반환
}

int main()
{
	char *line;
	int fd;

	fd = open("text.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	close(fd);

	return (0);
}
/*
 * 1. BUFFER_SIZE가 컴파일 시 랜덤 지정됨.
 *
 * 2. 그 버퍼 사이즈만큼 파일을 읽고 line에 개행 전까지의 문자열을 넣어줌.
 * 	새 문자열 할당 -> 개행전까지 문자열 입력-> *line = 새문자열 주소
 *
 * 3. 읽은 문자열을 개행 앞까지 line에 넣고, 읽은 문자열의 개행 뒷 부분을 다른 버퍼에 저장해놓음 (함수가 끝나도 사라지지 않는 static 변수에 저장)
 *
 * 4. 함수가 재 실행 되면 다시 사이즈만큼 읽은 문자열이 있을 것
 *
 * 5. 그 문자열과 이전에 static변수에 저장한 문자열을 합침
 * 	(if static변수 != 0) (strcat같은 함수로 합침)
 *
 * 6. 그 합친 문자열에서 개행 전까지 line에 넣어주고
 * (문자만날때까지 복사하는 함수)
 *
 * 7. static변수에 개행 이후의 문자열을 다시 넣어줌.(memmove?)
 *
 * ---------------------
 *  예외사항
 *  - EOF까지 읽어서 read의 리턴값이 0인 경우인데,
 *    마지막 읽은 문자열 사이에 또는 이전에 저장된 버퍼 내에 개행문자가 있는 경우?
 *    => 그럼 개행 전 문자열을 line에 넣고 그 이후 문자열은 출력이 안됨.
 *    => 어떻게 처리? 
 **/
