/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:47:13 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 18:13:14 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door.h"

static int	is_valid_file_extension(char *filename)
{
	int	offset;

	if (!ft_strrchr(filename, '.'))
		return (0);
	offset = ft_strlen(filename) - 4;
	if (ft_strncmp(".cub", filename + offset, 5) == 0)
		return (1);
	return (0);
}

static int	is_valid_input(int ac, char **av)
{
	int	fd;

	if (ac < 2)
		return (perr("no map specified"));
	if (ac > 2)
		return (perr("multiples arguments"));
	if (!is_valid_file_extension(av[1]))
		return (perr("invalid map extension"));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (perr("map doesnt exist or incorrect permissions"));
	close(fd);
	return (1);
}

int	validate_parameters_state(t_game *game, char *row, int fd)
{
	if (!game->params.north_texture || !game->params.south_texture
		|| !game->params.east_texture || !game->params.west_texture
		|| !is_valid_rgb(game))
		return (clean_gnl(row, fd), perr("invalid config file"));
	clean_gnl(row, fd);
	return (1);
}

int	init_config_params(t_game *game, char *filepath)
{
	char	*row;
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (!fd)
		return (0);
	if (!validate_identifiers(filepath))
		return (perr("invalid identifier"));
	row = ft_gnl(fd);
	if (!row)
		return (0);
	while (row && is_reserved_ch(*row, "NSEWFC\n"))
	{
		if (is_empty_line(&row, fd))
			continue ;
		if (!validate_parameter(game, &row, fd))
			return (0);
	}
	return (validate_parameters_state(game, row, fd));
}

int	input_validation(t_game *game, int ac, char **av)
{
	if (!is_valid_input(ac, av))
		return (0);
	if (!init_config_params(game, av[1]))
		return (0);
	return (1);
}
