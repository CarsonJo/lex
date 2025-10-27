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
static void init_opt(t_option* var, int argc)
{
	var->flag = 0;
	var->fd = malloc(sizeof(int) * argc);
	var->output_file = open("lex.yy.c", O_CREAT | O_RDWR, 0x600);
	var->s_start = malloc(sizeof(t_start_condition) * ARRAY_SIZE);
	var->x_start = malloc(sizeof(t_start_condition) * ARRAY_SIZE);
	var->name_var = malloc(sizeof(t_substitute) * ARRAY_SIZE);
	var->name_size = ARRAY_SIZE;
	var->s_size = ARRAY_SIZE;
	var->x_size = ARRAY_SIZE;
	var->s_start->name = 0;
	var->x_start->name = 0;
}
int main(int argc, char **argv)
{
	t_option	var;
	
	init_opt(&var, argc);
	check_option(argv, argc, &var.flag, var.fd);
	setlocale(LC_ALL, "");
	definition(&var);
	// printf("flag %x\n", flag);
	// int i = 0;
	// while (fd[i] >= 0)
	// {
	// 	printf("fd : %d\n", fd[i]);
	// 	print_file(fd[i]);
	// 	i++;
	// }
	free(var.fd);
}
