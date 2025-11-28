/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebilla <arebilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:42:45 by arebilla          #+#    #+#             */
/*   Updated: 2025/11/28 13:43:51 by arebilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <string.h>

static void	fill_buffer(int fd, t_buffer *buffer)
{
	ssize_t	read_bytes;

	read_bytes = read(fd, buffer->start, buffer->size);
	if (read_bytes < 0)
		return ;
	buffer->end = buffer->start + read_bytes;
	buffer->read = buffer->start;
	buffer->eof = (size_t)read_bytes < buffer->size;
}

static char	*copy_buffer(t_buffer *buffer, size_t len)
{
	char	*content;

	content = malloc(len);
	if (!content)
		return (NULL);
	ft_memcpy(content, buffer->read, len);
	buffer->read += len;
	return (content);
}

static t_line_buffer	*read_until_eol_or_eof(int fd, t_buffer *buffer,
												size_t *len_line)
{
	t_line_buffer	*line_buffer;
	char			*eol;
	size_t			len;
	char			*content;

	if (buffer->read == buffer->end)
		fill_buffer(fd, buffer);
	if (buffer->read == buffer->end)
		return (NULL);
	eol = (char *)ft_memchr(buffer->read, '\n', buffer->end - buffer->read);
	if (eol)
		len = eol - buffer->read + 1;
	else
		len = buffer->end - buffer->read;
	*len_line += len;
	content = copy_buffer(buffer, len);
	if (!content)
		return (NULL);
	line_buffer = new_line_buffer(content, len);
	if (buffer->eof || eol)
		line_buffer->next = NULL;
	else
		line_buffer->next = read_until_eol_or_eof(fd, buffer, len_line);
	return (line_buffer);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer = {{}, 0, 0, BUFFER_SIZE, 0};
	t_line_buffer	*line_buffer;
	char			*line;
	size_t			len_line;

	len_line = 0;
	line_buffer = read_until_eol_or_eof(fd, &buffer, &len_line);
	if (!line_buffer)
		return (NULL);
	line = malloc(len_line + 1);
	if (!line)
		return (NULL);
	line = contactenate_content(line, line_buffer);
	free_line_buffer(line_buffer);
	return (line);
}
