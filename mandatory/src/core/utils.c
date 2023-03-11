/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:25:15 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/11 15:49:54 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"
#include "door.h"

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
	if (FEATURE_FLAG_DOOR)
		return (get_map_with_door(fd, &game->map_width, &game->map_height));
	return (get_map(fd, &game->map_width, &game->map_height));
}
