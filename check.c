#include "main.h"

static void set_option(char **argv, int i, int *flag)
{
	int j = 0;

	while (argv[i][j])
	{
		switch (argv[i][j])
		{
			case OPTION_N:
				*flag |= OPTION_N_FLAG;
				break;
			case OPTION_T:
				*flag |= OPTION_T_FLAG;
				break;
			case OPTION_V:
				*flag |= OPTION_V_FLAG;
				break;
			default:
				break;
		}
		j++;
	}
}

static void open_src_file(char **argv, int *temp, int *fd)
{
	int i = 0;
	int j = 0;
	int holder;

	while (temp[i] > 0)
	{
		holder = open(argv[temp[i]], O_RDONLY);
		if (holder < 0)
		{
			perror("open");
			exit(1);//error to do
		}
		fd[j] = holder;
		j++;
		i++;
	}
	fd[j] = -1;
}

static void make_file(int *fd)
{
	char	*buffer = malloc(sizeof(char) * BUFFER_SIZE);
	int		ret;

	fd[0] = open("/tmp", __O_TMPFILE | O_RDWR, 0600);
	if (fd[0] < 0)
	{
		perror("open(TMPFILE)");
		exit(1);// error to do;
	}
	ret = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	while (ret > 0)
	{
		write(fd[0], buffer, ret);
		ret = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	}
	fd[1] = -1;
	lseek(fd[0], 0, SEEK_SET);
	free(buffer);
}

void check_option(char** argv, int argc, int* flag, int* fd)
{
	int *temp = malloc(sizeof(int) * (argc + 1));
	int	i = 1;
	int k = 0;
	int	bool_std = 0;

	while(i < argc)
	{
		if (!strcmp(argv[i], "-"))
			bool_std = 1;
		else if (argv[i][0] == '-')
			set_option(argv, i, flag);
		else
		{
			temp[k] = i;
			k++;
		}
		i++;
	}
	temp[k] = -1;
	if (!bool_std && temp[0] > 0)
		open_src_file(argv, temp, fd);
	else
		make_file(fd);
	free(temp);
}
