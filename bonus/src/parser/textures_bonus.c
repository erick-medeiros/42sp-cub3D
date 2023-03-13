/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:57:03 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/13 15:49:05 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	save_texture_path(t_game *game, char cardinal, char *path)
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

static int	is_valid_file(char *filepath)
{
	int		fd;
	char	*ext;
	char	*file;

	ext = ft_strrchr(filepath, '.');
	if (!ext || ft_strncmp(ext, ".xpm\n", 5))
		return (perr("expects .xpm file for textures"));
	file = ft_strtrim(filepath, " \n\t");
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(file);
		close(fd);
		return (perr("invalid file/permissions"));
	}
	free(file);
	close(fd);
	return (1);
}

static int	validate_texture(t_game *game, char **matrix,
	char *cardinal, char *err_msg)
{
	char	*path;

	path = get_filename(matrix[1]);
	if (!path)
		return (perr(err_msg));
	if (!is_valid_file(path))
	{
		free(path);
		return (0);
	}
	if (!save_texture_path(game, *cardinal, path))
	{
		free(path);
		return (perr("duplicated texture found"));
	}
	free(path);
	return (1);
}

static char	*get_identifier(char *row)
{
	char	**matrix;
	char	*id;

	matrix = get_matrix(row);
	if (!matrix)
		return (NULL);
	id = ft_strdup(matrix[0]);
	if (ft_strlen(id) > 2)
	{
		free(id);
		ft_free_matrix(matrix);
		return (NULL);
	}
	ft_free_matrix(matrix);
	return (id);
}

int	check_texture(t_game *game, char *row, char *cardinal, char *err_msg)
{
	char	**matrix;
	char	*id;

	id = get_identifier(row);
	if (!id)
		return (perr("invalid config file"));
	if (ft_strncmp(id, cardinal, 2) == 0 && ft_strlen(id) == 2)
	{
		matrix = get_matrix(row);
		if (!matrix[1])
		{
			free(id);
			ft_free_matrix(matrix);
			return (perr(err_msg));
		}
		if (!validate_texture(game, matrix, cardinal, err_msg))
		{
			free(id);
			return (ft_free_matrix(matrix), 0);
		}
		ft_free_matrix(matrix);
	}
	free(id);
	return (1);
}
