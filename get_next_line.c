/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andredos <andredos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:13:12 by andredos          #+#    #+#             */
/*   Updated: 2026/07/13 15:23:27 by andredos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	static int	size;
	char		*buff;
	int			bytes;
	char		*line;

	bytes = 1;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!nl_in_stash(stash, size) && (bytes > 0))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes > 0)
		{
			buff[bytes] = '\0';
			add_to_stash(&stash, &size, buff, bytes);
		}
	}
	if (bytes < 0 || (bytes == 0 && (!stash || !*stash)))
		return (free(buff), free(stash), stash = NULL, size = 0, NULL);
	if (remove_line_from_stash(&stash, &size, extract_line(&stash, &line)))
		return (free(buff), NULL);
	get_next_line_cleanup(&stash, &size);
	return (free(buff), line);
}

void	get_next_line_cleanup(char **stash, int *size)
{
	if (size == 0)
	{
		free(stash);
		stash = NULL;
	}
}

int	nl_in_stash(char *stash, int size)
{
	int	i;

	i = 0;
	if (stash == NULL || size == 0)
		return (0);
	while (i < size && stash[i] != '\0')
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
