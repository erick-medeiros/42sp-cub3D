/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 03:56:01 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 17:32:24 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "debug_bonus.h"

int	is_valid_attributes_with_door(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!is_reserved_ch(map[i][j], "01 NSEWFCDA\t\n"))
				return (0);
		}
	}
	return (1);
}

int	validate_identifiers_with_door(char *filepath)
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
		if (!is_reserved_ch(*row, "NSEWFC10DA \n"))
		{
			clean_gnl(row, fd);
			return (0);
		}
		free(row);
		row = ft_gnl(fd);
	}
	return (1);
}

void	close_door_and_update_matrix(t_game *game)
{
	t_px	pos;
	int		custom;

	pos.x = game->player.pos.x;
	pos.y = game->player.pos.y;
	custom = game->player.pos.y - DIST_TO_WALL - 1;
	if (game->map[custom][pos.x] == 'C')
		game->map[custom][pos.x] = 'D';
	custom = game->player.pos.y + DIST_TO_WALL + 1;
	if (game->map[custom][pos.x] == 'C')
		game->map[custom][pos.x] = 'D';
	custom = game->player.pos.x - DIST_TO_WALL - 1;
	if (game->map[pos.y][custom] == 'C')
		game->map[pos.y][custom] = 'D';
	custom = game->player.pos.x + DIST_TO_WALL + 1;
	if (game->map[pos.y][custom] == 'C')
		game->map[pos.y][custom] = 'D';
}

void	open_door_and_update_matrix(t_game *game)
{
	t_px	pos;

	pos.x = game->player.pos.x;
	pos.y = game->player.pos.y;
	if (game->map[pos.y - 1][pos.x] == 'D')
		game->map[pos.y - 1][pos.x] = 'C';
	if (game->map[pos.y + 1][pos.x] == 'D')
		game->map[pos.y + 1][pos.x] = 'C';
	if (game->map[pos.y][pos.x - 1] == 'D')
		game->map[pos.y][pos.x - 1] = 'C';
	if (game->map[pos.y][pos.x + 1] == 'D')
		game->map[pos.y][pos.x + 1] = 'C';
}

int	check_door_texture(t_game *game, char *row)
{
	char	**tokens;
	int		i;
	int		j;

	tokens = get_matrix(row);
	if (!tokens)
		return (0);
	i = 0;
	if (!tokens[i] || *tokens[1] == '\n')
		return (perr("door texture not found"));
	while (tokens[i])
		i++;
	if (i < 2)
	{
		ft_free_matrix(tokens);
		return (perr("door texture not found"));
	}
	game->door_sprites.textures = ft_calloc(sizeof(char *), i);
	i = 0;
	j = -1;
	while (tokens[++i])
		game->door_sprites.textures[++j] = ft_strtrim(tokens[i], " \n\t");
	ft_free_matrix(tokens);
	game->params.door_texture = game->door_sprites.textures[0];
	return (1);
}
