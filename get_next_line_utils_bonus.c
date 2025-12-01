/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebilla <arebilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 09:59:35 by arebilla          #+#    #+#             */
/*   Updated: 2025/12/01 09:59:40 by arebilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line_bonus.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char		*d;
	unsigned char const	*s;

	d = (unsigned char *)dest;
	s = (unsigned char const *)src;
	while (len--)
		*d++ = *s++;
	return (dest);
}

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char const	*s;

	s = (unsigned char const *)str;
	while (n--)
	{
		if ((unsigned char)c == *s)
			return ((void *)s);
		s++;
	}
	return (NULL);
}

t_line_buffer	*new_line_buffer(char *content, size_t len)
{
	t_line_buffer	*line_buffer;

	line_buffer = malloc(sizeof(t_line_buffer));
	if (!line_buffer)
		return (NULL);
	line_buffer->content = content;
	line_buffer->len = len;
	line_buffer->next = NULL;
	return (line_buffer);
}

void	free_line_buffer(t_line_buffer *line_buffer)
{
	if (line_buffer == NULL)
		return ;
	free(line_buffer->content);
	free_line_buffer(line_buffer->next);
	free(line_buffer);
}

char	*contactenate_content(char *line, t_line_buffer *line_buffer)
{
	size_t	len;

	len = 0;
	while (line_buffer)
	{
		ft_memcpy(line + len, line_buffer->content, line_buffer->len);
		len += line_buffer->len;
		line_buffer = line_buffer->next;
	}
	line[len] = '\0';
	return (line);
}
