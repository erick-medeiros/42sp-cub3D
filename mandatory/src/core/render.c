/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:09:30 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/09 12:02:01 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"
#include "raycaster.h"
#include "debug.h"
#include "minimap.h"

void	update_input(t_player *player, int map_width, int map_height)
{
	t_vector	move;
	t_vector	strafe;

	if (player->rotate_speed)
	{
		player->dir = rotate_vector(player->dir, player->rotate_speed);
		player->plane = rotate_vector(player->plane, player->rotate_speed);
	}
	if (player->move_speed)
	{
		move = mult_vector_scalar(player->dir, player->move_speed);
		move = add_vector(player->pos, move);
		if (move.x >= 0 && move.x < map_width)
			if (move.y >= 0 && move.y < map_height)
				player->pos = move;
	}
	if (player->strafe_speed)
	{
		strafe = rotate_vector(player->dir, M_PI_2);
		strafe = mult_vector_scalar(strafe, player->strafe_speed);
		strafe = add_vector(player->pos, strafe);
		if (strafe.x >= 0 && strafe.x < map_width)
			if (strafe.y >= 0 && strafe.y < map_height)
				player->pos = strafe;
	}
}

int	render(t_game *game)
{
	input_handler(game);
	update_input(&game->player, game->map_width, game->map_height);
	if (FEATURE_FLAG_MINIMAP && game->minimap.frame)
		draw_minimap(game);
	reset_canvas(game->canvas);
	raycaster(game, game->canvas);
	if (FEATURE_FLAG_MINIMAP && game->minimap.frame)
	{
		if (game->minimap.fullscreen)
			draw_layer(game->canvas, game->minimap.frame_fullscreen,
				game->minimap.pos_fullscreen, (t_px){0, 0});
		else
			draw_layer(game->canvas, game->minimap.frame,
				game->minimap.pos, (t_px){0, 0});
	}
	mlx_put_image_to_window(game->mlx, game->win, game->canvas->ptr, 0, 0);
	if (FEATURE_FLAG_FPS)
		fps_meter(game->mlx, -1);
	return (0);
}
