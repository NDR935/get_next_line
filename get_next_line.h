/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andredos <andredos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:13:58 by andredos          #+#    #+#             */
/*   Updated: 2026/07/12 18:59:17 by andredos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	safe_realoc(char **line, int new_size);
void	add_to_stash(char **stash, int *stash_size, char *buffer,
			int bytes_read);
int		get_line(char **stash, char **line);
void	remove_line_from_stash(char **stash, int *stash_size, int line_size);
void	ft_strncat(char *dest, char *src, int n);
int		nl_in_stash(char *stash, int stash_size);
void	get_next_line_cleanup(char **stash, int *stash_size);

#endif