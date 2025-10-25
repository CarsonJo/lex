#include "main.h"

void print_file(int fd)
{
	int		ret;
	char	buffer[BUFFER_SIZE + 1];

	ret = read(fd, buffer, BUFFER_SIZE);
	printf("\n\nMYFILE \n\n");
	buffer[BUFFER_SIZE] = 0;
	while (ret > 0)
	{
		write(1, buffer, ret);
		ret = read(fd, buffer, BUFFER_SIZE);
	}
}

int main(int argc, char **argv)
{
	int	flag = 0;
	int	*fd = malloc(sizeof(int) * argc);
	int	output = open("lex.yy.c", O_CREAT | O_RDWR, 0x600); 

	check_option(argv, argc, &flag, fd);
	setlocale(LC_ALL, "");
	definition(fd);
	// printf("flag %x\n", flag);
	// int i = 0;
	// while (fd[i] >= 0)
	// {
	// 	printf("fd : %d\n", fd[i]);
	// 	print_file(fd[i]);
	// 	i++;
	// }
	free(fd);
}
