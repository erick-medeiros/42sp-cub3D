/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 21:17:23 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/02/27 18:39:29 by frosa-ma         ###   ########.fr       */
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

char	*get_identifier(char *row)
{
	char	**matrix;
	char	*id;

	matrix = get_matrix(row);
	if (!matrix)
		return (NULL);
	id = ft_strdup(matrix[0]);
	if (ft_strlen(id) > 2)
		return (NULL);
	ft_free_matrix(matrix);
	return (id);
}

int	validate_file(char *filepath)
{
	int		fd;
	char	*ext;
	char	*file;

	ext = ft_strrchr(filepath, '.');
	if (!ext || ft_strncmp(ext, ".xpm\n", 5))
		return (perr("[-] expects .xpm file for textures"));
	file = ft_strtrim(filepath, " \n\t");
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(file);
		close(fd);
		return (perr("[-] invalid file/permissions"));
	}
	free(file);
	close(fd);
	return (1);
}

char	*get_filename(char *filename)
{
	if (!filename || ft_strncmp(filename, "\n", 2) == 0)
		return (NULL);
	return (ft_strdup(filename));
}

int	init_texture(t_game *game, char cardinal, char *path)
{
	if (cardinal == 'N')
	{
		if (game->params.north_texture)
			return (0);
		game->params.north_texture = ft_strtrim(path, "\n");
	}
	if (cardinal == 'S')
	{
		if (game->params.south_texture)
			return (0);
		game->params.south_texture = ft_strtrim(path, "\n");
	}
	if (cardinal == 'E')
	{
		if (game->params.east_texture)
			return (0);
		game->params.east_texture = ft_strtrim(path, "\n");
	}
	if (cardinal == 'W')
	{
		if (game->params.west_texture)
			return (0);
		game->params.west_texture = ft_strtrim(path, "\n");
	}
	return (1);
}
