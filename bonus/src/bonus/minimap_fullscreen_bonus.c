/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fullscreen_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:51:31 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 17:34:34 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "minimap_bonus.h"

void	init_minimap_fullscreen(t_game *game)
{
	game->minimap.scale_full = calcule_scale(game->map_width, game->map_height,
			game->canvas->width - (2 * game->minimap.edge_distance),
			game->canvas->height - (2 * game->minimap.edge_distance));
	game->minimap.frame_fullscreen = create_canvas(game->mlx,
			game->map_width * game->minimap.scale_full,
			game->map_height * game->minimap.scale_full);
	draw_map_2d(game, game->minimap.frame_fullscreen, game->minimap.scale_full);
	save_canvas_background(game->minimap.frame_fullscreen);
	game->minimap.pos_fullscreen.x = ((double) game->canvas->width / 2)
		- ((double) game->minimap.frame_fullscreen->width / 2);
	game->minimap.pos_fullscreen.y = ((double) game->canvas->height / 2)
		- ((double) game->minimap.frame_fullscreen->height / 2);
	game->minimap.fullscreen = FALSE;
}

void	draw_minimap_fullscreen_ray(t_game *game, t_engine *engine,
	double euclidian_dist)
{
	t_vector	start;
	t_vector	end;

	end = set_mag_vector(engine->ray_dir, euclidian_dist);
	start = mult_vector_scalar(game->player.pos, game->minimap.scale_full);
	end = mult_vector_scalar(end, game->minimap.scale_full);
	end = add_vector(start, end);
	draw_line(game->minimap.frame_fullscreen,
		start, end, MINIMAP_COLOR_RAY);
}

void	draw_fullscreen_minimap(t_game *game)
{
	t_vector	scaled_player;
	t_rect		player;
	t_vector	dir;

	reset_canvas(game->minimap.frame_fullscreen);
	scaled_player = mult_vector_scalar(game->player.pos,
			game->minimap.scale_full);
	player.x = scaled_player.x - 3;
	player.y = scaled_player.y - 3;
	player.width = 6;
	player.height = 6;
	draw_rectangle(game->minimap.frame_fullscreen,
		player, MINIMAP_COLOR_PLAYER);
	dir = mult_vector_scalar(game->player.dir, game->minimap.scale_full);
	dir = add_vector(scaled_player, dir);
	draw_line(game->minimap.frame_fullscreen,
		scaled_player, dir, MINIMAP_COLOR_PLAYER);
}
