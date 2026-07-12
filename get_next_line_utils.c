/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andredos <andredos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 16:09:17 by andredos          #+#    #+#             */
/*   Updated: 2026/07/12 19:01:13 by andredos         ###   ########.fr       */
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

void	add_to_stash(char **stash, int *stash_size,
	char *buffer, int bytes_read)
{
	int	i;

	i = 0;
	if (*stash == NULL)
	{
		*stash = malloc(bytes_read + 1);
		if (!*stash)
			return ;
		(*stash)[0] = '\0';
	}
	*stash_size += bytes_read;
	safe_realoc(stash, *stash_size + 1);
	ft_strncat(*stash, buffer, bytes_read);
	(*stash)[*stash_size] = '\0';
}

void	ft_strncat(char *dest, char *src, int n)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	dest[i] = '\0';
	j = 0;
	while (src[j] != '\0' && j < n)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
}

int	get_line(char **stash, char **line)
{
	int	i;

	i = 0;
	while ((*stash)[i] != '\0' && (*stash)[i] != '\n')
		i++;
	*line = malloc(i + 2);
	if (!*line)
		return (-1);
	i = 0;
	while ((*stash)[i] != '\0' && (*stash)[i] != '\n')
	{
		(*line)[i] = (*stash)[i];
		i++;
	}
	if ((*stash)[i] == '\n')
	{
		(*line)[i] = '\n';
		i++;
	}
	(*line)[i] = '\0';
	return (i);
}

void	remove_line_from_stash(char **stash, int *stash_size, int line_size)
{
	int		j;
	int		new_stash_size;
	char	*new_stash;

	new_stash_size = *stash_size - line_size;
	new_stash = malloc(new_stash_size + 1);
	if (!new_stash)
	{
		free(*stash);
		*stash = NULL;
		*stash_size = 0;
		return ;
	}
	j = 0;
	while (j < new_stash_size)
	{
		new_stash[j] = (*stash)[line_size + j];
		j++;
	}
	new_stash[j] = '\0';
	free(*stash);
	*stash = new_stash;
	*stash_size = new_stash_size;
}
