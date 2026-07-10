/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andredos <andredos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 16:09:17 by andredos          #+#    #+#             */
/*   Updated: 2026/07/10 17:54:06 by andredos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	safe_realoc(char **line, int new_size)
{
	char	*new_line;
	int		i;

	new_line = malloc(new_size);
	if (!new_line)
	{
		free(*line);
		*line = NULL;
		return ;
	}
	i = 0;
	while ((*line)[i] && i < new_size - 1)
	{
		new_line[i] = (*line)[i];
		i++;
	}
	new_line[i] = '\0';
	free(*line);
	*line = new_line;
}

void	*ft_calloc(int size)
{
	void	*line;

	line = malloc(size);
	if (!line)
		return (NULL);
	((char *)line)[0] = '\0';
	return (line);
}

int	get_fd_nl_size(int fd, int *size)
{
	char	current_char;
	int		bytes_read;

	*size = 0;
	while (1)
	{
		bytes_read = read(fd, &current_char, 1);
		if (bytes_read <= 0)
			break ;
		(*size)++;
		if (current_char == '\n')
			break ;
	}
	return (bytes_read);
}
