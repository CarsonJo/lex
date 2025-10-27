#ifndef MAIN_H
# define MAIN_H
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <locale.h>
# include <ctype.h>

# define OPTION_N 'n'
# define OPTION_V 't'
# define OPTION_T 'v'

# define OPTION_N_FLAG 1
# define OPTION_V_FLAG 2
# define OPTION_T_FLAG 4

#define BUFFER_SIZE 100
# include "gnl/get_next_line.h"
#define ARRAY_SIZE 100

#define ARRAY 1
#define PTR 0

typedef struct start_condition{
	char	*name;
}	t_start_condition;

typedef struct substitute{
	char	*name;
	char	*substitute;
}	t_substitute;

typedef struct option{
	int					flag;
	int					output_file;
	int					*fd;
	int					arr_ptr;
	int					num_pos;
	int					num_state;
	int					num_trans;
	int					num_parse_tree_node;
	int					num_packed_char_class;
	int					size_arr;
	t_start_condition*	s_start;
	t_start_condition*	x_start;
	t_substitute*		name_var;
	size_t				name_size;
	size_t				s_size;
	size_t				x_size;
}	t_option;


//check.c
void check_option(char** argv,int argc,int* flag, int* fd);

//definition
void definition(t_option *var);
#endif
