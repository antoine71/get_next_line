/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebilla <arebilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 22:09:41 by arebilla          #+#    #+#             */
/*   Updated: 2025/11/26 22:31:54 by arebilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	// TODO to implement
	return memcpy(dest, src, len);
}

void	*ft_memchr(const void *str, int c, size_t n)
{
	// TODO to implement
	return memchr(str, c, n);
}

t_line_buffer	*new_line_buffer(void)
{
	t_line_buffer	*line_buffer;

	line_buffer = malloc(sizeof(t_line_buffer));
	if (!line_buffer)
		return (NULL);
	line_buffer->content = NULL;
	line_buffer->len = 0;
	line_buffer->next = NULL;
	return (line_buffer);
}

void	free_line_buffer(t_line_buffer **line_buffer)
{
	if (*line_buffer == NULL)
		return ;
	free((*line_buffer)->content);
	free_line_buffer(&((*line_buffer)->next));
	free(*line_buffer);
}

char	*contactenate_line_buffer(t_line_buffer *line_buffer)
{
	size_t			len;
	size_t			len_counter;
	char			*line;
	t_line_buffer	*line_buffer_tmp;

	len = 0;
	line_buffer_tmp = line_buffer;
	while (line_buffer_tmp)
	{
		len += line_buffer_tmp->len;
		line_buffer_tmp = line_buffer_tmp->next;
	}
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	line_buffer_tmp = line_buffer;
	len_counter = 0;
	while (line_buffer_tmp)
	{
		ft_memcpy(line + len_counter, line_buffer_tmp->content, line_buffer_tmp->len);
		len_counter += line_buffer_tmp->len;
		line_buffer_tmp = line_buffer_tmp->next;
	}
	line[len] = '\0';
	return (line);
}
