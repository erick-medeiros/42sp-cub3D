/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:25:15 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/15 03:24:28 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "door_bonus.h"

void	player_orientation(t_player *player, char orientation)
{
	player->dir = create_vector(0, -1);
	player->plane = create_vector(FOV_RAD, 0);
	if (orientation == 'S')
	{
		player->dir = create_vector(0, 1);
		player->plane = create_vector(-FOV_RAD, 0);
	}
	else if (orientation == 'E')
	{
		player->dir = create_vector(1, 0);
		player->plane = create_vector(0, FOV_RAD);
	}
	else if (orientation == 'W')
	{
		player->dir = create_vector(-1, 0);
		player->plane = create_vector(0, -FOV_RAD);
	}
}

char	*start_map(t_game *game, int fd)
{
	return (get_map_with_door(fd, &game->map_width, &game->map_height));
}

int	is_door_open(t_game *game)
{
	if (game->map[(int)game->player.pos.y - 1][(int)game->player.pos.x] == 'C'
	|| game->map[(int)game->player.pos.y + 1][(int)game->player.pos.x] == 'C'
	|| game->map[(int)game->player.pos.y][(int)game->player.pos.x - 1] == 'C'
	|| game->map[(int)game->player.pos.y][(int)game->player.pos.x + 1] == 'C'
	)
		return (1);
	return (0);
}

static int	validate_bonus_texture(char *texture)
{
	int	fd;

	fd = open(texture, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	is_valid_bonus_textures(t_game *game)
{
	int	i;

	i = -1;
	while (game->door_sprites.textures[++i])
		if (!validate_bonus_texture(game->door_sprites.textures[i]))
			return (perr("invalid door texture found"));
	i = -1;
	while (game->sprites.textures[++i])
		if (!validate_bonus_texture(game->sprites.textures[i]))
			return (perr("invalid animation texture found"));
	return (1);
}
