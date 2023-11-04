/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakhaev <abakhaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:49:46 by abakhaev          #+#    #+#             */
/*   Updated: 2023/11/04 15:19:52 by abakhaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return (str);
}

char *cut_line(char **stockbuf)
{
	int i; 
	i = 0;
	int len; 
	len = 0;
	char *line;
	char *tmp;

	while ((*stockbuf)[i] != '\n' && (*stockbuf)[i] != '\0')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	int j;
	j = 0;
	while (j < i)
	{
		line[j] = (*stockbuf)[j];
		j++;
	}
	line[i] = '\0';
	if ((*stockbuf)[i] == '\n')
		i++;
	while ((*stockbuf)[i + len] != '\0')
		len++;
	tmp = (char *)malloc((len + 1) * sizeof(char));
	j = 0;
	while (j < len)
	{
		tmp[j] = (*stockbuf)[i + j];
		j++;
	}
	tmp[len] = '\0';
	free(*stockbuf);
	*stockbuf = tmp;
	return (line);
}


char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return (NULL);
}
