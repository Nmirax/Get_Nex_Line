/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abakhaev <abakhaev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:49:46 by abakhaev          #+#    #+#             */
/*   Updated: 2023/11/07 14:44:23 by abakhaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Looks for a newline character in the given linked list. */
int found_newline(t_list *stockbuf)
{
    t_list *current = stockbuf;

    while (current)
    {
        char *content = (char *)current->content;
        while (*content)
        {
            if (*content == '\n')
                return (1);
            content++;
        }
        current = current->next;
    }
    return (0);
}

/* Returns a pointer to the last node in our stash */
t_list *ft_lst_get_last(t_list *stockbuf)
{
    t_list *last = stockbuf;
    while (last && last->next)
    {
        last = last->next;
    }
    return (last);
}


/* Calculates the number of chars in the current line, including the trailing
 * \n if there is one, and allocates memory accordingly. */
void generate_line(char **line, t_list *stockbuf)
{
    int len = 0;
    t_list *current = stockbuf;

    while (current)
    {
        char *content = (char *)current->content;
        while (*content)
        {
            if (*content == '\n')
                break;
            len++;
            content++;
        }
        current = current->next;
    }
    *line = malloc(sizeof(char) * (len + 1));
}

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return (len);
}
/* Frees the entire stash. */
void free_stockbuf(t_list *stockbuf)
{
    t_list *current = stockbuf;
    while (current)
    {
        free(current->content);
        t_list *next = current->next;
        free(current);
        current = next;
    }
}