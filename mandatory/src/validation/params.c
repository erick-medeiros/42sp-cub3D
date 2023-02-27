/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:25:15 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/02/27 18:26:26 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_texture(t_game *game, char **matrix,
	char *cardinal, char *err_msg)
{
	char	*path;

	path = get_filename(matrix[1]);
	if (!path)
		return (perr(err_msg));
	if (!validate_file(path))
		return (0);
	if (!init_texture(game, *cardinal, path))
		return (perr("[-] duplicated texture found"));
	return (1);
}

static int	check_texture(t_game *game, char *row,
	char *cardinal, char *err_msg)
{
	char	**matrix;
	char	*id;

	id = get_identifier(row);
	if (!id)
		return (0);
	if (ft_strlen(id) == 1 || (ft_strncmp(id, cardinal, 2) == 0
			&& ft_strlen(id) == 2))
	{
		matrix = get_matrix(row);
		if (!matrix[1])
		{
			ft_free_matrix(matrix);
			return (perr(err_msg));
		}
		if (!is_valid_texture(game, matrix, cardinal, err_msg))
		{
			ft_free_matrix(matrix);
			return (0);
		}
		ft_free_matrix(matrix);
	}
	free(id);
	return (1);
}

static int	init_textures(t_game *game, char *row)
{
	if (*row == 'N')
		return (check_texture(game, row, "NO", "[-] missing north textures"));
	else if (*row == 'S')
		return (check_texture(game, row, "SO", "[-] missing south textures"));
	else if (*row == 'E')
		return (check_texture(game, row, "EA", "[-] missing east textures"));
	else if (*row == 'W')
		return (check_texture(game, row, "WE", "[-] missing west textures"));
	return (0);
}

static int	check_texture_param(t_game *game, char **row, int fd)
{
	int	valid;

	valid = init_textures(game, *row);
	if (!valid)
	{
		clean_gnl(*row, fd);
		return (0);
	}
	free(*row);
	*row = ft_gnl(fd);
	return (1);
}

int	init_config_params(t_game *game, char *filepath)
{
	char	*row;
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (!fd)
		return (0);
	row = ft_gnl(fd);
	if (!row)
		return (0);
	while (row && is_reserved_ch(*row, "NSEW"))
		if (!check_texture_param(game, &row, fd))
			return (0);
	if (!game->params.north_texture || !game->params.south_texture
		|| !game->params.east_texture || !game->params.west_texture)
		return (perr("[-] invalid config file"));
	clean_gnl(row, fd);
	return (1);
}
