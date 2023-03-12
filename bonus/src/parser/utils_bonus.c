/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:54:54 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 17:32:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

int	clean_map(t_game *game)
{
	ft_free_matrix(game->map);
	game->map = NULL;
	return (0);
}
