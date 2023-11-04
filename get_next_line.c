/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakhaev <abakhaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:47:29 by abakhaev          #+#    #+#             */
/*   Updated: 2023/11/04 14:52:00 by abakhaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static char *stockbuf;
	char *buf;
	char *line;
	int i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));

	i = 0;
	
	while((i = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[i] = '\0';
		stockbuf = ft_strjoin(stockbuf, buf);

		if(ft_strchr(buf, '\n'))
			break;
	}
	free(buf);
	if (i <= 0)
		return (NULL); //line detected or error
	
	line = cut_line(&stockbuf);
	return (line);
}
