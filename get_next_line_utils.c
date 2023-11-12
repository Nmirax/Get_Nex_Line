/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakhaev <abakhaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:36:46 by abakhaev          #+#    #+#             */
/*   Updated: 2023/11/12 18:22:59 by abakhaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "get_next_line.h"

/* Looks for a newline character in the given linked list. */

int	found_newline(t_list *stockbuf)
{
	int		i;
	t_list	*current;

	if (stockbuf == NULL)
		return (0);
	current = ft_lst_get_last(stockbuf);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/* Returns a pointer to the last node in our stockbuf */

t_list	*ft_lst_get_last(t_list *stockbuf)
{
	t_list	*current;

	current = stockbuf;
	while (current && current->next)
		current = current->next;
	return (current);
}

/* Calculates the number of chars in the current line, including the trailing
 * \n if there is one, and allocates memory accordingly. */

void	generate_line(char **line, t_list *stockbuf)
{
	int	i;
	int	len;

	len = 0;
	while (stockbuf)
	{
		i = 0;
		while (stockbuf->content[i])
		{
			if (stockbuf->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stockbuf = stockbuf->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

/* Free the entire stockbuf. */

void	free_stockbuf(t_list *stockbuf)
{
	t_list	*current;
	t_list	*next;

	current = stockbuf;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}
