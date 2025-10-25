#include "../main.h"

static void c_fragment(int *fd, int *line_number)
{
	char *line;

	line = get_next_line(fd);
	*line_number++;
	while (line)
	{
		if (line[0] == '%' && line[1] == '}')
			return ;

		line = get_next_line(fd);
		*line_number++;
	}
	printf("premature end of file: line %d", *line_number);
	exit(1);
}

static void c_fragment_line(char *line)
{

}

static void percent_directive(char *line)
{

}

static void name(char* line)
{

}

void	definition(int *fd, int *output)
{
	char	*line;
	int		line_number = 1;

	line = get_next_line(fd);
	while(line)
	{
		if (isspace(line[0]))
			c_fragment_line(line);
		else if(line[0] == '%')
			percent_directive(line);
		else
			name(line);
		free(line);
		line = get_next_line(fd);
		line_number++;
	}
}
