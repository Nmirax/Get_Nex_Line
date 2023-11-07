#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct s_list
{
	void 	*content;
struct s_list *next;
} 			t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
t_list *ft_lst_get_last(t_list *stockbuf);
int found_newline(t_list *stockbuf);
void add_to_stockbuf(t_list **stockbuf,char *buf, int readed);
void	read_and_stockbuf(int fd, t_list **stockbuf, int *readed_ptr);
t_list *ft_lst_get_last(t_list *stockbuf);


#endif