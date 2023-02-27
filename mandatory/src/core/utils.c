/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:25:15 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/02/27 11:54:17 by frosa-ma         ###   ########.fr       */
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

void	clean_params(t_params *params)
{
	if (!params)
		return ;
	free(params->north_texture);
	free(params->south_texture);
	free(params->east_texture);
	free(params->west_texture);
}

void	clean_canvas(t_game *game)
{
	game->canvas = destroy_canvas(game->mlx, game->canvas);
	game->canvas = destroy_canvas(game->mlx, game->canvas);
	game->north_texture = destroy_canvas(game->mlx, game->north_texture);
	game->canvas = destroy_canvas(game->mlx, game->canvas);
	game->canvas = destroy_canvas(game->mlx, game->canvas);
	game->south_texture = destroy_canvas(game->mlx, game->south_texture);
	game->canvas = destroy_canvas(game->mlx, game->canvas);
	game->west_texture = destroy_canvas(game->mlx, game->west_texture);
	game->east_texture = destroy_canvas(game->mlx, game->east_texture);
	game->frame_3d = destroy_canvas(game->mlx, game->frame_3d);
}
