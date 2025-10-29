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
	
	var->s_start = malloc(sizeof(t_start_condition) * ARRAY_SIZE);
	memset(var->s_start, 0, sizeof(t_start_condition) * ARRAY_SIZE);
	var->x_start = malloc(sizeof(t_start_condition) * ARRAY_SIZE);
	memset(var->x_start, 0, sizeof(t_start_condition) * ARRAY_SIZE);
	var->name_var = malloc(sizeof(t_substitute) * ARRAY_SIZE);
	memset(var->name_var, 0, sizeof(t_substitute) * ARRAY_SIZE);

	var->arr_ptr = 0;
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
	if (var.flag & OPTION_T_FLAG)
		var.output_file = STDOUT_FILENO;
	else
		var.output_file = open("lex.yy.c", O_CREAT | O_RDWR, S_IRWXU);
	if (var.output_file < 0)
	{
		perror("output_file");
		exit(1);
	}
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
	printf("S_START AND X_START\n");
	printf("x_start:\n");
	size_t i = 0;
	while (i < var.x_size && var.x_start[i].name)
		printf("name: %s\n", var.x_start[i++].name);
	printf("s_start:\n");
	i = 0;
	while (i < var.s_size && var.s_start[i].name)
		printf("name: %s\n", var.s_start[i++].name);
	printf("NAME AND SUB\n");
	i = 0;
	while (i < var.name_size && var.name_var[i].name)
	{
		printf("name: %s\\sub: %s\n", var.name_var[i].name, var.name_var[i].substitute);
		i++;
	}
	printf("P: %d\n", var.num_pos);
	printf("N: %d\n", var.num_state);
	printf("A: %d\n", var.num_trans);
	printf("E: %d\n", var.num_parse_tree_node);
	printf("K: %d\n", var.num_packed_char_class);
	printf("O: %d\n", var.size_arr);
	printf("array(1) or pointer(0): %d\n", var.arr_ptr);
	free(var.s_start);
	free(var.x_start);
	free(var.name_var);
	free(var.fd);
}
