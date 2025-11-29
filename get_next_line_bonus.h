/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arebilla <arebilla@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:46:38 by arebilla          #+#    #+#             */
/*   Updated: 2025/11/29 08:15:14 by arebilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_RANGE
#  define FD_RANGE 1024
# endif

# include <stddef.h>

typedef struct s_buffer
{
	char	start[BUFFER_SIZE];
	char	*read;
	char	*end;
	int		eol;
	int		eof;
}	t_buffer;

typedef struct s_line_buffer
{
	char					*content;
	size_t					len;
	struct s_line_buffer	*next;
}	t_line_buffer;

char			*get_next_line(int fd);
t_line_buffer	*new_line_buffer(char *content, size_t len);
void			free_line_buffer(t_line_buffer *line_buffer);
char			*contactenate_content(char *line, t_line_buffer *line_buffer);
void			*ft_memcpy(void *dest, const void *src, size_t len);
void			*ft_memchr(const void *str, int c, size_t n);

#endif
