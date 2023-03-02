/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:54:54 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/01 20:33:54 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**get_matrix(char *row)
{
	char	**matrix;

	matrix = NULL;
	if (ft_strchr(row, '\t'))
		matrix = ft_split(row, '\t');
	else
		matrix = ft_split(row, ' ');
	if (!matrix)
		return (NULL);
	return (matrix);
}

char	*get_filename(char *filename)
{
	if (!filename || ft_strncmp(filename, "\n", 2) == 0)
		return (NULL);
	return (ft_strdup(filename));
}

int	is_player_found(char **map)
{
	int	player;
	int	i;
	int	j;

	player = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (is_reserved_ch(map[i][j], "NSEW"))
				player++;
	}
	if (player != 1)
		return (0);
	return (1);
}

int	is_row_empty(char **row, int fd)
{
	free(*row);
	*row = ft_gnl(fd);
	if (!*row)
		return (0);
	return (1);
}

int	is_empty_line(char **row, int fd)
{
	if (**row != '\n')
		return (0);
	free(*row);
	*row = ft_gnl(fd);
	return (1);
}
