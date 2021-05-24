
/*
int main()
{
	char *line;
	int fd;
	int	n;
	int	i;

	fd = open("43_with_nl", O_RDONLY);
	i = 0;
	while ((n = get_next_line(-12301, &line)) >= 0)
	{
		i++;
		printf("n : %d\n", n);
		printf("line : %s\n", line);
		free(line);
		if (n == 0)
			break ;
	}
	if (n == -1)
		printf("n : -1\n");
	close(fd);

	return (0);
}
*/
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
