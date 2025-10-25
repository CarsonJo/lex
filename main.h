#ifndef MAIN_H
# define MAIN_H
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <locale.h>
# include <ctype.h>
# include "gnl/get_next_line_bonus.h"

# define OPTION_N 'n'
# define OPTION_V 't'
# define OPTION_T 'v'

# define OPTION_N_FLAG 1
# define OPTION_V_FLAG 2
# define OPTION_T_FLAG 4

#define BUFFER_SIZE 100
//check.c
void check_option(char** argv,int argc,int* flag, int* fd);

//definition
void defintion(int *fd);
#endif
