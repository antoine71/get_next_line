/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebilla <arebilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:42:45 by arebilla          #+#    #+#             */
/*   Updated: 2025/11/26 22:26:56 by arebilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static void	fill_buffer(int fd, t_buffer *buffer)
{
	ssize_t	read_bytes;

	read_bytes = read(fd, buffer->content, buffer->size);
	if (read_bytes <= 0)
	{
		buffer->len = 0;
		return ;
	}
	buffer->len = read_bytes;
	buffer->read_index = 0;
	if ((size_t)read_bytes < buffer->size)
		buffer->eof = 1;
}

static char	*empty_buffer(t_buffer *buffer, size_t len)
{
	char	*content;
	
	content = malloc(len);
	if (!content)
		return (NULL);
	ft_memcpy(content, buffer->content + buffer->read_index, len);
	buffer->read_index += len;
	return (content);
}

static t_line_buffer	*read_until_eol_or_eof(int fd, t_buffer *buffer)
{
	t_line_buffer	*line_buffer;
	char	*eol;
	size_t	len;

	if (!buffer->len || buffer->read_index == buffer->len)
		fill_buffer(fd, buffer);
	if (!buffer->len)
		return (NULL);
	eol = ft_memchr(buffer->content + buffer->read_index, '\n', buffer->size - buffer->read_index);
	if (eol)
		len = eol - buffer->content - buffer->read_index + 1;
	else
		len = buffer->len - buffer->read_index;
	line_buffer = new_line_buffer();
	if (!line_buffer)
		return (NULL);
	line_buffer->content = empty_buffer(buffer, len);
	if (!line_buffer->content)
		return (NULL);
	line_buffer->len = len;
	if (buffer->eof || eol)
		line_buffer->next = NULL;
	else
		line_buffer->next = read_until_eol_or_eof(fd, buffer);
	return (line_buffer);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer = { {}, BUFFER_SIZE, 0, 0, 0 };
	t_line_buffer	*line_buffer;
	char	*line;

	if (buffer.eof && buffer.read_index == buffer.len)
		return (NULL);
	line_buffer = read_until_eol_or_eof(fd, &buffer);
	if (!line_buffer)
		return (NULL);
	line = contactenate_line_buffer(line_buffer);
	free_line_buffer(&line_buffer);
	return (line);
}
