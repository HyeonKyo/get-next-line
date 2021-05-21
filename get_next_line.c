/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonkki <hyeonkki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:48:09 by hyeonkki          #+#    #+#             */
/*   Updated: 2021/05/20 16:55:27 by hyeonkki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	gnl_strcpy(char *dest, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (src == 0)
		return ;
	while (i + 1 < size && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (size != 0)
		dest[i] = 0;
}

int		clean(int fd, char *buf, char **backup, int n)
{
	if (buf)
		free(buf);
	if (backup[fd]);
		free((char *)backup[fd]);
	buf = 0;
	backup[fd] = 0;
	return (n);
}

int		gnl_get_one_line(int fd, char **line, char **backup, char *buf)
{
	char	*tmp;

	tmp = ft_strchr(backup[fd], '\n') + 1;
	if (tmp == 0)
		tmp = ft_strchr(backup[fd], '\0') + 1;
	*line = (char *)malloc((tmp - backup[fd]) * sizeof(char));
	if (*line == 0)
		return (clean(fd, buf, backup, -1));
	gnl_strcpy(*line, backup[fd], tmp - backup[fd]);
	if (*line[0] != 0)
	{
		if(!gnl_strmove(backup[fd], tmp, ft_strlen(tmp) + 1))
			return (clean(fd, buf, backup[fd], -1));
		free(buf);
		return (1);
	}
	else
		return (clean(fd, buf, backup, 0));
}

int		get_next_line(int fd, char **line)
{
	ssize_t		n_bytes;
	char		*buf;
	static char	*backup[OPEN_MAX + 1];
	char		*tmp;

	if (BUFFER_SIZE < 1 || !(buf = (char *)malloc(BUFFER_SIZE + 1))
		|| fd < 0 || fd > OPEN_MAX)
		return (-1);
	ft_bzero(buf, BUFFER_SIZE + 1);
	while ((n_bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		//일단 buf와 backup을 합쳐줌.
		backup[fd] = ft_strjoin(backup[fd], buf);
		//backup에 개행이 있다면 -> line에 할당하고 개행까지 복사해준 후 
		//backup의 개행 후를 처음으로 옮겨놓음.
		//그 후 buf를 해제하고 리턴
		if (ft_strchr(backup[fd], '\n'))
			return (gnl_get_one_line(fd, line, backup, buf));
		//buf에 개행이 없는 경우 이므로 다시 읽기위해 buf를 비워줌.
		ft_bzero(buf, BUFFER_SIZE + 1);
	}
	if (n_bytes == 0)
		return (gnl_get_one_line(fd, line, backup, buf));
	else
		return (clean(fd, buf, backup[fd], -1));
}

int main()
{
	int             fd;
	int             i;
	int             j;
	char    		*line = 0;
	char			*lineadress[66];

	j = 1;
	
	printf("\n==========================================\n");
	printf("========== TEST 1 : The Alphabet =========\n");
	printf("==========================================\n\n");

	if (!(fd = open("files/alphabet", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		lineadress[j - 1] = line;
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);

	if (i == -1)
		printf ("\nError in Fonction - Returned -1\n");
	else if (j == 66)
		printf("\nRight number of lines\n");
	else if (j != 66)
		printf("\nNot Good - Wrong Number Of Lines\n");
	while (--j > 0)
		free(lineadress[j - 1]);
	j = 1;

	printf("\n==========================================\n");
	printf("========= TEST 2 : Empty Lines ===========\n");
	printf("==========================================\n\n");

	if (!(fd = open("files/empty_lines", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);

	if (i == -1)
		printf ("\nError in Fonction - Returned -1\n");
	else if (j == 9)
		printf("\nRight number of lines\n");
	else if (j != 9)
		printf("\nNot Good - Wrong Number Of Lines\n");
	
	j = 1;
	printf("\n==========================================\n");
	printf("======== TEST 3 : The Empty File =========\n");
	printf("==========================================\n\n");

	if (!(fd = open("files/empty_file", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);

	if (i == -1)
		printf ("\nError in Fonction - Returned -1\n");
	else if (j == 1)
		printf("\nRight number of lines\n");
	else if (j != 1)
		printf("\nNot Good - Wrong Number Of Lines\n");
	j = 1;
	printf("\n==========================================\n");
	printf("========= TEST 4 : One New Line ==========\n");
	printf("==========================================\n\n");

	if (!(fd = open("files/1_newline", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);

	if (i == -1)
		printf ("\nError in Fonction - Returned -1\n");
	else if (j == 2)
		printf("\nRight number of lines\n");
	else if (j != 2)
		printf("\nNot Good - Wrong Number Of Lines\n");
	j = 1;
	printf("\n==========================================\n");
	printf("========= TEST 5 : Four New Lines ========\n");
	printf("==========================================\n\n");

	if (!(fd = open("files/4_newlines", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);

	if (i == -1)
		printf ("\nError in Fonction - Returned -1\n");
	else if (j == 5)
		printf("\nRight number of lines\n");
	else if (j != 5)
		printf("\nNot Good - Wrong Number Of Lines\n");
	j = 1;
	printf("\n==========================================\n");
	printf("============== TEST 6 : 42 ===============\n");
	printf("==========================================\n\n");

	if (!(fd = open("files/41_char", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);
	if (!(fd = open("files/42_char", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{

		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);
	if (!(fd = open("files/43_char", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("|%s\n", line);
		free(line);
		j++;
	}
	printf("|%s\n", line);
	free(line);
	close(fd);

	if (i == -1)
		printf ("\nError in Fonction - Returned -1\n");
	else if (j == 1)
		printf("\nRight number of lines\n");
	else if (j != 1)
		printf("\nNot Good - Wrong Number Of Lines\n");
	j = 1;
	printf("\n==========================================\n");
	printf("============= TEST 7 : Marge =============\n");
	printf("==========================================\n\n");

	int fd2;

	if (!(fd = open("files/half_marge_top", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	if (!(fd2 = open("files/half_marge_bottom", O_RDONLY)))
	{
		printf("\nError in open\n");
		return (0);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		j++;
	}
	free(line);
	while ((i = get_next_line(fd2, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		j++;
	}
	printf("%s\n", line);
	free(line);
	close(fd);
	close(fd2);

	if (i == -1)
		printf ("\nError in Fonction - Returned -1\n");
	else if (j == 25)
		printf("\nRight number of lines\n");
	else if (j != 25)
		printf("\nNot Good - Wrong Number Of Lines\n");
	j = 1;
	printf("\n==========================================\n");
	printf("========= TEST 8 : Wrong Input ===========\n");
	printf("==========================================\n\n");

	if (get_next_line(180, &line) == -1)
		printf("Well Done, you return -1 if no FD\n\n");
	else
		printf("Not Good, you don't return -1 if no FD\n\n");
	return (0);
}


/*
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
		if (n == 0)
			break ;
	}
	close(fd);

	return (0);
}*/

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
