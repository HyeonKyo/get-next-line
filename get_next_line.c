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

int		get_next_line(int fd, char **line)
{
	ssize_t		n_bytes;
	char		*buf[MAX_FD]; //fd의 최댓값 넣기
	static char	*str;
	char		*tmp;
	int			flag;

	flag = 0;
	if (!buf[fd] || BUFFER_SIZE < 1 || fd < 0 || !*line ||
		!(buf[fd] = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	n_bytes = read(fd, buf[fd], BUFFER_SIZE);
	if (n_bytes < 0)
		return (-1);
	if (n_byte == 0)
		buf[fd][ft_strlen + 1] = 0;
	if (!*str)
		str = ft_strdup(buf);
	else
	{
		while (!tmp = ft_strchr(str, '\n') && !flag)
		{
			flag = 1;
			ft_strcat(str, buf[fd]);
		}
		if (!tmp)
		{
			*line = (char *)malloc((tmp - str + 1) * sizeof(char));
			ft_strlcpy(*line, str, tmp - str);
			ft_memmove(str, tmp, ft_strlen(tmp) + 1);
			if (!flag)
				ft_strcat(str, buf[fd]);
		}
		else
		{
			// 읽었을 때 이전 문자열까지 합해서 개행이 없으면 *line에 무엇을?
		}
	}
	free(buf[fd]);
	if (!n_bytes)
		return (0);
	return (1);
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
