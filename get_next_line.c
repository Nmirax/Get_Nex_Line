/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakhaev <abakhaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:58:44 by abakhaev          #+#    #+#             */
/*   Updated: 2023/11/14 17:17:41 by abakhaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stockbuf = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (!read_and_stockbuf(fd, &stockbuf))
	{
		free_stockbuf(stockbuf);
		stockbuf = NULL;
		return (NULL);
	}
	if (stockbuf == NULL)
		return (NULL);
	extract_line(stockbuf, &line);
	clean_stockbuf(&stockbuf);
	if (line[0] == '\0')
	{
		free_stockbuf(stockbuf);
		stockbuf = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

int	read_and_stockbuf(int fd,	t_list **stockbuf)
{
	char	*buf;
	int		readed;	

	readed = 1;
	while (!found_newline(*stockbuf) && readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return (0);
		readed = (int)read(fd, buf, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buf);
			return (0);
		}
		if (readed == 0)
		{
			free(buf);
			break ;
		}
		buf[readed] = '\0';
		add_to_stockbuf(stockbuf, buf, readed);
		free(buf);
	}
	return (1);
}

void	add_to_stockbuf(t_list **stockbuf, char *buf, int readed)
{
	int		i;
	t_list	*last;
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (readed + 1));
	if (new->content == NULL)
		return ;
	i = 0;
	while (buf[i] && i < readed)
	{
		new->content[i] = buf[i];
		i++;
	}
	new->content[i] = '\0';
	if (*stockbuf == NULL)
	{
		*stockbuf = new;
		return ;
	}
	last = ft_lst_get_last(*stockbuf);
	last->next = new;
}

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

void	clean_stockbuf(t_list **stockbuf)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;

	clean = malloc(sizeof(t_list));
	if (stockbuf == NULL || clean == NULL)
		return ;
	clean->next = NULL;
	last = ft_lst_get_last(*stockbuf);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	j = ft_strlen(last->content);
	clean->content = malloc(sizeof(char) * (j - i) + 1);
	if (clean->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean->content[j++] = last->content[i++];
	clean->content[j] = '\0';
	free_stockbuf(*stockbuf);
	*stockbuf = clean;
}
