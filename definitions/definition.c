#include "../main.h"

void write_line(int line_number, int fd)
{
	
}

static void add_start_condition(t_start_condition** arr, size_t *size, char *name)
{
	int i = 0;
	int start;

	while (isblank(name[i])) //trim space before
		i++;
	start = 0;
	while (name[i] && !isblank(name[i]))//trim space after
		i++;
	name[i] = 0;
	i = 0;
	while(i < *size && *arr[i]->name && strcmp(*arr[i]->name, &name[start])) //check if name exist or name array full
		i++;
	if (i >= *size)
	{
		*arr = realloc(*arr, sizeof(t_start_condition) * *size * 2);
		memset((*arr) + *size, 0, size);
		*size *= 2;
	}
	else if(*arr[i]->name)
	{
		printf("start condition %s declared twice", *arr[i]->name);
		return ;
	}
	else
		*arr[i]->name = strdup(name);
}

static void	add_name_substitute(char* line, int sub, t_substitute** var, int *size)
{
	int	i = 0;

	while (i < *size && var[i]->name && strcmp(var[i]->name, line))
		i++;
	if (i >= *size)
	{
		*var = realloc(*var, sizeof(t_substitute) * *size * 2);
		memset(*var + *size, 0, size);
		*size *= 2;
	}
	else if (*var[i]->name)
	{
		printf("name defined twice");
		exit(1); //error todo
	}
	else
	{
		*var[i]->name = strdup(line);
		*var[i]->substitute = strdup(&line[sub]);
	}
}

static void c_fragment(t_option* var, int *line_number)
{
	char *line;

	line = get_next_line(var->fd);
	*line_number++;
	fprintf(var->output_file, "#line %d", line_number);
	while (line)
	{
		write(var->output_file, line, strlen(line));
		if (line[0] == '%' && line[1] == '}')
			return ;
		line = get_next_line(var->fd);
		*line_number++;
	}
	printf("premature end of file: line %d", *line_number);
	exit(1);
}

static void c_fragment_line(char *line, int line_number, t_option* var)
{
	fprintf(var->output_file, "#line %d", line_number);
	write(var->output_file, line, strlen(line));
}

static int percent_directive(char *line, t_option* var)
{
	int	i = 1;

	if (!strncmp(line, "%array", 7))
		var->arr_ptr = ARRAY;
	else if (!strncmp(line, "%pointer", 9))
		var->arr_ptr = PTR;
	else if (line[i] && isblank(line[i + 1]))
	{
		switch (line[i])
		{
			case 'p':
				var->num_pos = atoi(&line[2]);
				break;
			case 'n':
				var->num_state = atoi(&line[2]);
				break;
			case 'a':
				var->num_trans = atoi(&line[2]);
				break;
			case 'e':
				var->num_parse_tree_node = atoi(&line[2]);
				break;
			case 'k':
				var->num_packed_char_class = atoi(&line[2]);
				break;
			case 'o':
				var->size_arr = atoi(&line[2]);
				break;
			case 's':
				add_start_condition(&var->s_start, &var->s_size, &line[2]);
				break;
			case 'S':
				add_start_condition(&var->s_start, &var->s_size, &line[2]);
				break;
			case 'x':
				add_start_condition(&var->x_start, &var->x_size, &line[2]);
				break;
			case 'X':
				add_start_condition(&var->x_start, &var->x_size, &line[2]);
				break;
			case '%':
				return (1);
			default:
				break;
		}
	}
	else if (line[i] == '%')
		return(1);
	return (0);
}

static void name(char* line, t_option* var)
{
	int	i = 0;
	int	sub;

	if (isalpha(line[i]) || line[i] == '_')
	{
		while (isalnum(line[i]) || line[i] == '_')
			i++;
		if (!isblank(line[i]))
			return ;
		line[i++] = 0;
		while (isblank(line[i]))
			i++;
		sub = i;
		while (line[i] && !isblank(line[i]))
			i++;
		line[i] = 0;
		add_name_substitute(line, sub, &var->name_var, &var->name_size);
	}
}

void	definition(t_option *var)
{
	char	*line;
	int		line_number = 1;

	line = get_next_line(var->fd);
	while(line)
	{
		if (isspace(line[0]))
			c_fragment_line(line, line_number, var);
		else if(line[0] == '%' && percent_directive(line, var))
			return ;
		else
			name(line, var);
		free(line);
		line = get_next_line(var->fd);
		line_number++;
	}
}
