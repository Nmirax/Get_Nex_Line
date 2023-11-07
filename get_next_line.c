/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakhaev <abakhaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:47:29 by abakhaev          #+#    #+#             */
/*   Updated: 2023/11/07 14:59:24 by abakhaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*get_next_line(int fd)
{
	static t_list	*stockbuf = NULL;
	char			*line;
	int             readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	// 1. read from fd and add to linked list
	read_and_stockbuf(fd, &stockbuf, &readed);
	if (stockbuf == NULL)
		return (NULL);
	// 2. extract from stash to line
	extract_line(&stockbuf, &line);
	// 3. clean up stash
	clean_stockbuf(&stockbuf);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

void    read_and_stockbuf(int fd, t_list **stockbuf, int *readed_ptr)
{
	char	*buf;

	*readed_ptr = 1;
	while (!found_newline(*stockbuf) && *readed_ptr != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		*readed_ptr = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stockbuf == NULL && *readed_ptr == 0) || *readed_ptr == -1)
		{
			free(buf);
			return ;
		}
		buf[*readed_ptr] = '\0';
		add_to_stockbuf(stockbuf, buf, *readed_ptr);
		free(buf);
	}
}


void add_to_stockbuf(t_list **stockbuf, char *buf, int readed)
{
	int i;
	t_list *last;
	t_list *new;
	
	new = malloc(sizeof(t_list));
	if (!new)
		return;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (readed + 1));
	if (!new->content)
	{
		free(new);
		return;
	}
	i = 0;
	while (buf[i] && i < readed)
	{
		((char *)new->content)[i] = buf[i];
		i++;
	}
	((char *)new->content)[i] = '\0';
	if (*stockbuf == NULL)
	{
		*stockbuf = new;
		return;
	}
	last = ft_lst_get_last(*stockbuf);
	last->next = new;
}

void    extract_line(t_list **stockbuf, char **line)
{
	int i;
	int j;
	t_list *current;

	current = *stockbuf;

	if (current == NULL)
		return;
	j = 0;
	while (current)
	{
		i = 0;
		while (((char *)(current->content))[i]) 
		{
			if (((char *)(current->content))[i] == '\n')
			{
				(*line)[j++] = ((char *)(current->content))[i++];
				break;
			}
			(*line)[j++] = ((char *)(current->content))[i++];
		}
		current = current->next;
	}

	(*line)[j] = '\0';
	clean_stockbuf(stockbuf);
}

void clean_stockbuf(t_list **stockbuf)
{
	t_list *last;
	t_list *clean_up;
	int i;
	int j;

	if (*stockbuf == NULL)
		return;

	clean_up = malloc(sizeof(t_list));
	if (clean_up == NULL)
		return;

	clean_up->next = NULL;
	last = ft_lst_get_last(*stockbuf);
	i = 0;
	while (last->content && ((char *)(last->content))[i] && ((char *)(last->content))[i] == '\n')
		i++;

	if (last->content && ((char *)(last->content))[i] != '\0')
	{
		clean_up->content = malloc(sizeof(char) * (ft_strlen((char *)(last->content)) - i + 1));
		if (clean_up->content == NULL)
		{
			free(clean_up);
			return;
		}

		j = 0;
		while (((char *)(last->content))[i])
			((char *)(clean_up->content))[j++] = ((char *)(last->content))[i++];

		((char *)(clean_up->content))[j] = '\0';

		free_stockbuf(*stockbuf);
		*stockbuf = clean_up;
	}
	else
	{
		free_stockbuf(*stockbuf);
		free(clean_up);
		*stockbuf = NULL;
	}
}
