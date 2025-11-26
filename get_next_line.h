/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebilla <arebilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 13:13:35 by arebilla          #+#    #+#             */
/*   Updated: 2025/11/26 22:19:05 by arebilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

#include <stddef.h>

typedef struct s_buffer {
	char	content[BUFFER_SIZE];
	size_t	size;
	size_t	len;
	size_t	read_index;
	int		eof;
} t_buffer;

typedef struct s_line_buffer {
	char					*content;
	size_t					len;
	struct s_line_buffer	*next;
} t_line_buffer;

char			*get_next_line(int fd);
t_line_buffer	*new_line_buffer(void);
void			free_line_buffer(t_line_buffer **line_buffer);
char			*contactenate_line_buffer(t_line_buffer *line_buffer);
void			*ft_memcpy(void *dest, const void *src, size_t len);
void			*ft_memchr(const void *str, int c, size_t n);

#endif
