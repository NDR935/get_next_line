/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andredos <andredos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 18:47:58 by andredos          #+#    #+#             */
/*   Updated: 2026/07/29 19:09:28 by andredos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;
	int		line_count;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	line_count = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("Line %d: %s\n", line_count++, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
