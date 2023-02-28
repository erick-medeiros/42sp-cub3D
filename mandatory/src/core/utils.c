/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:25:15 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/02/28 20:15:59 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *game)
{
	game->player.plane = create_vector(FOV_RAD, 0);
	game->player.pos = create_vector(0, 0);
	game->player.dir = create_vector(0, 0);
	game->player.movement = create_vector(0, 0);
	game->player.strafe = create_vector(0, 0);
	game->player.move_speed = MOVEMENT_SPEED;
	game->player.strafe_speed = STRAFE_SPEED;
	game->player.rotate_speed = 0;
}

void	init_params(t_game *game)
{
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->west_texture = NULL;
	game->east_texture = NULL;
	game->ceilling_color = separate_argb_color(0xFFFFFF);
	game->floor_color = separate_argb_color(0x000000);
	game->params.north_texture = NULL;
	game->params.south_texture = NULL;
	game->params.east_texture = NULL;
	game->params.west_texture = NULL;
}

void	init_textures(t_game *game)
{
	game->north_texture = create_canvas_texture(game->mlx,
			game->params.north_texture);
	game->south_texture = create_canvas_texture(game->mlx,
			game->params.south_texture);
	game->west_texture = create_canvas_texture(game->mlx,
			game->params.west_texture);
	game->east_texture = create_canvas_texture(game->mlx,
			game->params.east_texture);
}

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
