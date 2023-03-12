/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:25:15 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 18:42:11 by eandre-f         ###   ########.fr       */
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
