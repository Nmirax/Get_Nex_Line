/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakhaev <abakhaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:49:46 by abakhaev          #+#    #+#             */
/*   Updated: 2023/11/07 12:24:35 by abakhaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//search new line in the buf

int found_newline(t_list *stockbuf)
{
	int	i;
	t_list *current;

	if(stockbuf == NULL)
		return(0);
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

	/*REturns  pointer to the last in my stockbuf*/

	t_list *ft_lst_get_last(t_list *stockbuf)
	{
		t_list *current;
		
		current = stockbuf;
		while(current && current ->next)
				current = current ->next;
		return(current);
	}

	
	void	generate_line(char **line, t_list *stockbuf)
	{
		int i;
		int len;

		len = 0;
		while (stockbuf)
		{	
			i = 0;
			while(stockbuf->content[i])
			{
				if(stockbuf->content[i] == '\n')
				{
					len ++;
					break;
				}
				len++;
				i++;
			}
			stockbuf = stockbuf->next;
		}
		*line = malloc(sizeof(char) * (len + 1)

	}