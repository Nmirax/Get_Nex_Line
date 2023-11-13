/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakhaev <abakhaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:36:52 by abakhaev          #+#    #+#             */
/*   Updated: 2023/11/13 14:12:25 by abakhaev         ###   ########.fr       */
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
	// 1. read from fd and add to linked list
	read_and_stockbuf(fd, &stockbuf);
	if (stockbuf == NULL)
		return (NULL);
	// 2. extract from stash to line
	extract_line(stockbuf, &line);
	// 3. clean up stockbuf)
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

/* Uses read() to add characters to the stockbuf */

void read_and_stockbuf(int fd, t_list **stockbuf)
{
    char *buf;
    int readed;

    readed = 1;
    while (!found_newline(*stockbuf) && readed != 0)
    {
        buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if (buf == NULL)
        {
            // Gestion de l'erreur d'allocation de mémoire pour buf
            return;
        }

        readed = (int)read(fd, buf, BUFFER_SIZE);
        if (readed == -1)
        {
            
            free(buf);
            break;  // Sortir de la boucle en cas d'erreur de lecture
        }

        if (readed == 0)
        {
            // Vous avez atteint la fin du fichier
            free(buf);
            break;  // Sortir de la boucle
        }

        buf[readed] = '\0';
        add_to_stockbuf(stockbuf, buf, readed);
        free(buf);

    }

}

/* Adds the content of our buffer to the end of our stash */

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

/* Extracts all characters from our stash and stores them in out line.
 * stopping after the first \n it encounters */

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

/* After extracting the line that was read, we don't need those characters
 * anymore. This function clears the stockbuf so only the characters that have
 * not been returned at the end of get_next_line remain in our static stockbuf. */

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
	clean->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (clean->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean->content[j++] = last->content[i++];
	clean->content[j] = '\0';
	free_stockbuf(*stockbuf);
	*stockbuf = clean;
}

