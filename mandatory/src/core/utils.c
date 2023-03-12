/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:25:15 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 18:24:05 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (get_map(fd, &game->map_width, &game->map_height));
}
