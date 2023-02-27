/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:30:12 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/27 11:39:59 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "cub3d.h"
#include "debug.h"
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
	engine->line_height = 1 * game->frame_3d->height / engine->perp_wall_dist;
	height_mid = game->frame_3d->height / 2;
	// debug_vector("ray_dir", engine->ray_dir);
	// printf("line_height %i engine->perp_wall_dist %lf\n", engine->line_height, engine->perp_wall_dist);
	engine->line_start = height_mid - engine->line_height / 2;
	engine->line_end = height_mid + engine->line_height / 2;

	// int temp;
	// temp = fmaxf(engine->line_start, engine->line_end);
	// temp = fminf(temp, game->frame_3d->height - 1);
	// engine->line_start = fminf(engine->line_start, engine->line_end);
	// engine->line_start = fmaxf(engine->line_start, game->frame_3d->height - 1);
	// engine->line_end = temp;

	// if (engine->line_start < 0)
	// 	engine->line_start = 0;
	// if (engine->line_end >= game->frame_3d->height)
	// 	engine->line_end = game->frame_3d->height - 1;
	if (engine->hit_side == HIT_EAST || engine->hit_side == HIT_WEST)
		engine->wall_hit_x = game->player.pos.y
			+ (engine->perp_wall_dist * engine->ray_dir.y);
	else
		engine->wall_hit_x = game->player.pos.x
			+ (engine->perp_wall_dist * engine->ray_dir.x);
	engine->wall_hit_x -= floor(engine->wall_hit_x);
}

void	draw_full(t_game *game, t_engine *engine, int pixel)
{
	double color = 0x000000;
	if (engine->hit_side == HIT_EAST)
		color = 0x0000FF;
	else if (engine->hit_side == HIT_WEST)
		color = 0xFF0000;
	else if (engine->hit_side == HIT_SOUTH)
		color = 0x00FF00;
	else if (engine->hit_side == HIT_NORTH)
		color = 0xFFFF00;
	draw_line(game->frame_3d,
		create_vector(pixel, engine->line_start),
		create_vector(pixel, engine->line_end),
		color);
}

void	raycaster_draw_line(t_game *game, t_engine *engine, int pixel)
{
	t_img *texNum;
	if (engine->hit_side == HIT_EAST)
		texNum = game->east_texture;
	else if (engine->hit_side == HIT_WEST)
		texNum = game->west_texture;
	else if (engine->hit_side == HIT_SOUTH)
		texNum = game->south_texture;
	else
		texNum = game->north_texture;
	// double		color;
	raycaster_get_line(game, engine);
	// draw_full(game, engine, pixel);
	
	int texWidth = 64;
	int texHeight = 64;
	int texX = (int)(engine->wall_hit_x * (double)texWidth);
	if (engine->hit_side == HIT_EAST || engine->hit_side == HIT_WEST)
		// if (engine->ray_dir.x > 0)
			texX = texWidth - texX - 1;
	if (engine->hit_side == HIT_SOUTH || engine->hit_side == HIT_NORTH)
		// if (engine->ray_dir.y < 0)
			texX = texWidth - texX - 1;
	printf("wall_hit_x %lf texX %d\n", engine->wall_hit_x, texX);
	double step = 1.0 * texHeight / engine->line_height;
	if (engine->line_end > engine->line_start)
	{
		double texPos = (engine->line_start - (double)game->frame_3d->height / 2 + (double)engine->line_height / 2) * step;
		// printf("textPos %lf\n", texPos);
		// printf("start %d end %d sum %lf texPos %lf step %lf X %d\n", 
		// 	engine->line_start, engine->line_end,
		// 	(engine->line_start - (double)game->frame_3d->height / 2 + (double)engine->line_height / 2),
		//  	texPos, step, texX);
		int y = engine->line_start;
		while (y < engine->line_end)
		{
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			// printf("certo y %i tex Y %d texPos %lf\n", y, texY, texPos);
			t_argb color = mlx_get_argb_image_pixel(texNum, texX, texY);
			mlx_put_image_pixel(game->frame_3d, pixel, y, color.argb);
			y++;
		}
	}
	else
	{
		double texPos = (engine->line_end - (double)game->frame_3d->height / 2 + (double)engine->line_height / 2) * step;
		// texPos = 0;
		// printf("textPos %lf\n", texPos);
		// printf("start %d end %d sum %lf texPos %lf step %lf X %d\n", 
		// 	engine->line_start, engine->line_end,
		// 	engine->line_end - (double)game->frame_3d->height / 2 + (double)engine->line_height / 2,
		//  	texPos, step, texX);
		int y = engine->line_end;
		while (y < engine->line_start)
		{
			int texY = (int)texPos & (texHeight - 1);
			// printf("errado y %i tex Y %d texPos %lf\n", y, texY, texPos);
			texPos -= step;
			t_argb color = mlx_get_argb_image_pixel(texNum, texX, texY);
			mlx_put_image_pixel(game->frame_3d, pixel, y, color.argb);
			y++;
		}
	}
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
