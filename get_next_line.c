/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andredos <andredos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:13:12 by andredos          #+#    #+#             */
/*   Updated: 2026/07/10 17:54:18 by andredos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	int			line_size;
	char		current_char;
	int			bytes_read;

	if (fd < 0)
		return (NULL);
	line_size = 0;
	line = ft_calloc(1);
	if (!line)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, &current_char, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (line_size == 0)
            {
                free(line);
                return (NULL);
            }
			if (line_size > 0)
                break ;
            free(line);
            return (NULL);
		}
		if (current_char == '\n')
		{
			line[line_size++] = '\n';
			break ;
		}
		safe_realoc(&line, line_size + 2);
		if (!line)
			return (NULL);
		line[line_size] = current_char;
		line_size++;
	}
	line[line_size] = '\0';
	return (line);
}
