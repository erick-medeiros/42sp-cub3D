/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:30:12 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/25 18:31:31 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "cub3d.h"
#include "feature_flags.h"

static t_vector	raycaster_ray_dir(t_img *img, t_player player, int pixel)
{
	double		mult;
	t_vector	camera_pixel;
	t_vector	ray_dir;

	mult = 2 * ((double)pixel / img->width) - 1;
	camera_pixel = mult_vector_scalar(player.plane, mult);
	ray_dir = add_vector(player.dir, camera_pixel);
	return (ray_dir);
}

static void	raycaster_get_line(t_game *game, t_engine *engine)
{
	int	height_mid;

	if (engine->hit_side == HIT_EAST || engine->hit_side == HIT_WEST)
		engine->perp_wall_dist = fabs(engine->wall_hit.x - game->player.pos.x
				+ (((double)1 - engine->step_x) / 2)) / engine->ray_dir.x;
	else
		engine->perp_wall_dist = fabs(engine->wall_hit.y - game->player.pos.y
				+ (((double)1 - engine->step_y) / 2)) / engine->ray_dir.y;
	engine->line_height = game->frame_3d->height / engine->perp_wall_dist;
	height_mid = game->frame_3d->height / 2;
	engine->line_start = height_mid - (engine->line_height / 2);
	engine->line_end = height_mid + (engine->line_height / 2);
}

void	raycaster_draw_line(t_game *game, t_engine *engine, int pixel)
{
	double		color;
	t_vector	start;
	t_vector	end;

	raycaster_get_line(game, engine);
	start = create_vector(pixel, engine->line_start);
	end = create_vector(pixel, engine->line_end);
	color = 0x000000;
	if (engine->hit_side == HIT_EAST)
		color = 0x0000FF;
	else if (engine->hit_side == HIT_WEST)
		color = 0xFF0000;
	else if (engine->hit_side == HIT_SOUTH)
		color = 0x00FF00;
	else if (engine->hit_side == HIT_NORTH)
		color = 0xFFFF00;
	draw_line(game->frame_3d, start, end, color);
}

t_img	*raycaster(t_game *game)
{
	t_engine	engine;
	int			pixel;

	pixel = 0;
	while (pixel < game->frame_3d->width)
	{
		engine.ray_dir = raycaster_ray_dir(game->frame_3d, game->player, pixel);
		dda_calcule_delta_dist(&engine);
		dda_calcule_dist_to_side(&engine, game->player);
		raycaster_run_dda(game, &engine);
		raycaster_draw_line(game, &engine, pixel);
		if (FEATURE_FLAG_MINIMAP)
			draw_minimap_ray(game, &engine, engine.ray_dir);
		pixel++;
	}
	return (game->frame_3d);
}
