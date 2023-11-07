/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakhaev <abakhaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:47:29 by abakhaev          #+#    #+#             */
/*   Updated: 2023/11/07 12:31:29 by abakhaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static t_list *stockbuf;
	char *line;
	int readed;

	/*verification error              i can read,open return NULL*/	
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd,&line, 0) < 0)
	return (NULL);
	readed = 1; /*go next while*/
	line = NULL;

	// 1. read fd and add to stockbuf
	
		read_and_stockbuf(fd,&stockbuf,&readed);
		if (!stockbuf)
		return (NULL);
		
	return(line);
	// 2. send the list stockbuf to line
	extrac_line(stockbuf,&line)
	// 3. clear stockbuf

}
	//read the list and add the list to stockbuf

void	read_and_stockbuf(int fd, t_list **stockbuf, int *readed_ptr)

{
	char	*buf;
	int		readed;

	readed = 1;
	while (!found_newline(*stockbuf) && readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		readed = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stockbuf == NULL && readed == 0) || readed == -1)
		{
			free(buf);
			return ;
		}
		buf[readed] = '\0';
		add_to_stash(stockbuf, buf, readed);
		free(buf);
	}
}
	/*Adds the content of our buffer to the end of the stockbuf*/
	
void add_to_stockbuf(t_list **stockbuf,char *buf, int readed)

{
	int i;
	
	t_list *last;
	t_list *new;
	
new = malloc(sizeof(t_list));
	if(!new)
		return;
	new->next == NULL;
	new->content = malloc(sizeof(char) * (readed + 1));
	if(!new->content)
		return (NULL);
	i = 0;
	while(buf[i] && i < readed)
	{
		new->content[i] = buf[i];
		i++;
	}
	new->content[i] ='\0';
		if(*stockbuf == NULL)
		{
			*stockbuf = new;
			return;
		}
		last = ft_lst_get_last(*stockbuf);
		last->next = new;
}

/*Extract all characteres from my stockbuf and and stock on the out line.
stopping after the first \n it encounters*/

void	extract_line(t_list *stockbuf, char **line)	
{
	int	i;
	int	j;

	if (stockbuf == NULL)
		return ;
	generate_line(line, stockbuf);
	if (*line == NULL)
		return ;
	j = 0;
	while (stockbuf)
	{
		i = 0;
		while (stockbuf->content[i])
		{
			if (stockbuf->content[i] == '\n')
			{
				(*line)[j++] = stockbuf->content[i];
				break ;
			}
			(*line)[j++] = stockbuf->content[i++];
		}
		stockbuf = stockbuf->next;
	}
	(*line)[j] = '\0';
}