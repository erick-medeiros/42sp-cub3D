/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:25:15 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 17:35:07 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "feature_flags_bonus.h"
#include "door_bonus.h"

static int	validate_config_row(t_game *game, char *row)
{
	if (*row == 'N')
		return (check_texture(game, row, "NO", "missing north textures"));
	else if (*row == 'S')
		return (check_texture(game, row, "SO", "missing south textures"));
	else if (*row == 'E')
		return (check_texture(game, row, "EA", "missing east textures"));
	else if (*row == 'W')
		return (check_texture(game, row, "WE", "missing west textures"));
	else if (*row == 'F')
		return (check_rgb_color(game, row, 'F', "floor color not found"));
	else if (*row == 'C')
		return (check_rgb_color(game, row, 'C', "ceil color not found"));
	else if (FEATURE_FLAG_DOOR && *row == 'D')
		return (check_door_texture(game, row));
	else if (FEATURE_FLAG_DOOR && *row == 'A')
		return (check_animated_texture(game, row));
	return (0);
}

int	validate_parameter(t_game *game, char **row, int fd)
{
	if (!validate_config_row(game, *row))
	{
		clean_gnl(*row, fd);
		return (0);
	}
	free(*row);
	*row = ft_gnl(fd);
	return (1);
}

int	validate_identifiers(char *filepath)
{
	char	*row;
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (!fd)
		return (0);
	row = ft_gnl(fd);
	if (!row)
		return (0);
	while (row)
	{
		if (!is_reserved_ch(*row, "NSEWFC10 \n"))
		{
			clean_gnl(row, fd);
			return (0);
		}
		free(row);
		row = ft_gnl(fd);
	}
	return (1);
}
