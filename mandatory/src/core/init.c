/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:10:06 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/11 04:10:05 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"

void	game_init(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->window_width = WINDOW_WIDTH;
	game->window_height = WINDOW_HEIGHT;
	game->canvas = NULL;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->control.strafe_right = FALSE;
	game->control.strafe_left = FALSE;
	game->control.walk_up = FALSE;
	game->control.walk_down = FALSE;
	game->control.rotate_left = FALSE;
	game->control.rotate_right = FALSE;
	init_player(game);
	init_params(game);
	game->minimap.frame = NULL;
	game->control.mouse.x = 0;
	game->control.mouse.y = 0;
	game->config.mouse = FEATURE_FLAG_MINIMAP;
	game->door_range = 0;
}

void	init_player(t_game *game)
{
	game->player.plane = create_vector(FOV_RAD, 0);
	game->player.pos = create_vector(0, 0);
	game->player.dir = create_vector(0, 0);
	game->player.movement = create_vector(0, 0);
	game->player.strafe = create_vector(0, 0);
	game->player.move_speed = 0;
	game->player.strafe_speed = 0;
	game->player.rotate_speed = 0;
}

void	init_params(t_game *game)
{
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->west_texture = NULL;
	game->east_texture = NULL;
	game->ceilling_color.r = -1;
	game->ceilling_color.g = -1;
	game->ceilling_color.b = -1;
	game->floor_color.r = -1;
	game->floor_color.g = -1;
	game->floor_color.b = -1;
	game->params.north_texture = NULL;
	game->params.south_texture = NULL;
	game->params.east_texture = NULL;
	game->params.west_texture = NULL;
	game->params.floor.r = NULL;
	game->params.floor.g = NULL;
	game->params.floor.b = NULL;
	game->params.ceil.r = NULL;
	game->params.ceil.g = NULL;
	game->params.ceil.b = NULL;
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
	if (FEATURE_FLAG_DOOR)
		game->door_texture = create_canvas_texture(game->mlx,
				"assets/wolftex/pics_xpm/door_0.xpm");
}
