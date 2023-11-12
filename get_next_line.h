#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h> // REMOVE FOR PUSH
# include <stdlib.h>

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct	s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
int 	found_newline(t_list *stockbuf);
t_list	*ft_lst_get_last(t_list *stockbuf);
void	read_and_stockbuf(int fd, t_list **stockbuf);
void	add_to_stockbuf(t_list **stockbuf, char *buf, int readed);
void	extract_line(t_list *stockbuf, char **line);
void	generate_line(char **line, t_list *stockbuf);
void	clean_stockbuf(t_list **stockbuf);
int 	ft_strlen(const char *str);
void	free_stockbuf(t_list *stockbuf);
#endif