/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebilla <arebilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 09:59:07 by arebilla          #+#    #+#             */
/*   Updated: 2025/12/01 10:20:57 by arebilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

static void	fill_buffer(int fd, t_buffer *buffer)
{
	ssize_t	read_bytes;
	size_t	size;

	if (BUFFER_SIZE > 0x7ffff000)
		size = 0x7ffff000;
	else
		size = BUFFER_SIZE;
	read_bytes = read(fd, buffer->start, size);
	if (read_bytes < 0)
	{
		buffer->end = buffer->start;
		buffer->read = buffer->start;
		buffer->error = 1;
		return ;
	}
	buffer->end = buffer->start + read_bytes;
	buffer->read = buffer->start;
	buffer->eof = (read_bytes == 0);
}

static char	*copy_buffer(t_buffer *buffer, size_t len)
{
	char	*content;

	content = malloc(len);
	if (!content)
	{
		buffer->error = 1;
		return (NULL);
	}
	ft_memcpy(content, buffer->read, len);
	buffer->read += len;
	return (content);
}

size_t	check_eol(t_buffer *buffer)
{
	char	*eol;
	size_t	len;

	eol = (char *)ft_memchr(buffer->read, '\n', buffer->end - buffer->read);
	if (eol)
	{
		buffer->eol = 1;
		len = eol - buffer->read + 1;
	}
	else
		len = buffer->end - buffer->read;
	return (len);
}

static t_line_buffer	*read_until_eol_or_eof(int fd, t_buffer *buffer)
{
	t_line_buffer	*line_buffer;
	size_t			len;
	char			*content;

	if (buffer->read == buffer->end)
		fill_buffer(fd, buffer);
	if (buffer->read == buffer->end || buffer->error)
		return (NULL);
	len = check_eol(buffer);
	buffer->len_line += len;
	content = copy_buffer(buffer, len);
	if (!content)
		return (NULL);
	line_buffer = new_line_buffer(content, len);
	if (!line_buffer)
	{
		free(content);
		buffer->error = 1;
		return (NULL);
	}
	if (!buffer->eof && !buffer->eol)
		line_buffer->next = read_until_eol_or_eof(fd, buffer);
	return (line_buffer);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer[FD_RANGE];
	t_line_buffer	*line_buffer;
	char			*line;

	if (fd < 0 || fd > FD_RANGE)
		return (NULL);
	buffer[fd].len_line = 0;
	buffer[fd].error = 0;
	buffer[fd].eol = 0;
	line_buffer = read_until_eol_or_eof(fd, &buffer[fd]);
	if (!line_buffer || buffer[fd].error)
	{
		free_line_buffer(line_buffer);
		return (NULL);
	}
	line = malloc(buffer[fd].len_line + 1);
	if (!line)
	{
		free_line_buffer(line_buffer);
		return (NULL);
	}
	line = contactenate_content(line, line_buffer);
	free_line_buffer(line_buffer);
	return (line);
}
