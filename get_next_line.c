/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andredos <andredos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:13:12 by andredos          #+#    #+#             */
/*   Updated: 2026/07/12 18:55:11 by andredos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	static int	stash_size;
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*line;

	while (!nl_in_stash(stash, stash_size))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (stash == NULL || stash[0] == '\0')
				return (free(stash), stash = NULL, NULL);
			else
				break ;
		}
		buffer[bytes_read] = '\0';
		add_to_stash(&stash, &stash_size, buffer, bytes_read);
	}
	remove_line_from_stash(&stash, &stash_size, get_line(&stash, &line));
	get_next_line_cleanup(&stash, &stash_size);
	return (line);
}

void	get_next_line_cleanup(char **stash, int *stash_size)
{
	if (stash_size == 0)
	{
		free(stash);
		stash = NULL;
	}
}

int	nl_in_stash(char *stash, int stash_size)
{
	int	i;

	i = 0;
	if (stash == NULL || stash_size == 0)
		return (0);
	while (i < stash_size && stash[i] != '\0')
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
