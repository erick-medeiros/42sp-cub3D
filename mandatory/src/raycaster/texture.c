/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:09:45 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/27 19:37:21 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"

static t_hit	which_side_hit(t_engine *engine)
{
	if (engine->hit_side == HIT_X)
	{
		if (engine->step_x == 1)
			return (HIT_EAST);
		else
			return (HIT_WEST);
	}
	if (engine->hit_side == HIT_Y)
	{
		if (engine->step_y == 1)
			return (HIT_SOUTH);
		else
			return (HIT_NORTH);
	}
	return (0);
}

// void	raycaster_fill_one_color(t_game *game, t_engine *engine, int pixel)
// {
// 	double	color;
// 	t_hit	hit_side;

// 	hit_side = which_side_hit(engine);
// 	color = 0x000000;
// 	if (hit_side == HIT_EAST)
// 		color = 0x0000FF;
// 	else if (hit_side == HIT_WEST)
// 		color = 0xFF0000;
// 	else if (hit_side == HIT_SOUTH)
// 		color = 0x00FF00;
// 	else if (hit_side == HIT_NORTH)
// 		color = 0xFFFF00;
// 	draw_line(game->frame_3d,
// 		create_vector(pixel, engine->line_start),
// 		create_vector(pixel, engine->line_end),
// 		color);
// }

static void	raycaster_get_texture(t_game *game, t_engine *engine)
{
	t_hit	hit_side;

	hit_side = which_side_hit(engine);
	if (hit_side == HIT_EAST)
		engine->texture = game->east_texture;
	else if (hit_side == HIT_WEST)
		engine->texture = game->west_texture;
	else if (hit_side == HIT_SOUTH)
		engine->texture = game->south_texture;
	else
		engine->texture = game->north_texture;
}

static void	raycaster_get_line(t_game *game, t_engine *engine)
{
	int	height_mid;

	if (engine->hit_side == HIT_X)
		engine->perp_wall_dist = fabs(engine->wall_hit.x - game->player.pos.x
				+ (((double)1 - engine->step_x) / 2)) / engine->ray_dir.x;
	else
		engine->perp_wall_dist = fabs(engine->wall_hit.y - game->player.pos.y
				+ (((double)1 - engine->step_y) / 2)) / engine->ray_dir.y;
	engine->perp_wall_dist = fabs(engine->perp_wall_dist);
	engine->line_height = 1 * game->frame_3d->height / engine->perp_wall_dist;
	height_mid = game->frame_3d->height / 2;
	engine->line_start = height_mid - engine->line_height / 2;
	engine->line_end = height_mid + engine->line_height / 2;
	if (engine->line_start < 0)
		engine->line_start = 0;
	if (engine->line_end >= game->frame_3d->height)
		engine->line_end = game->frame_3d->height - 1;
	if (engine->hit_side == HIT_X)
		engine->wall_hit_x = game->player.pos.y
			+ (engine->perp_wall_dist * engine->ray_dir.y);
	else
		engine->wall_hit_x = game->player.pos.x
			+ (engine->perp_wall_dist * engine->ray_dir.x);
	engine->wall_hit_x -= floor(engine->wall_hit_x);
	raycaster_get_texture(game, engine);
}

void	raycaster_draw_line(t_game *game, t_engine *engine, int pixel)
{
	int		tex_y;
	int		tex_x;
	int		y;
	double	step;
	double	tex_pos;

	raycaster_get_line(game, engine);
	tex_x = (int)(engine->wall_hit_x * engine->texture->width);
	if (engine->hit_side == HIT_X && engine->ray_dir.x > 0)
			tex_x = engine->texture->width - tex_x - 1;
	if (engine->hit_side == HIT_Y && engine->ray_dir.y < 0)
			tex_x = engine->texture->width - tex_x - 1;
	step = 1.0 * engine->texture->height / engine->line_height;
	tex_pos = (engine->line_start - (double)game->frame_3d->height / 2
			+ (double)engine->line_height / 2) * step;
	y = engine->line_start;
	while (y < engine->line_end)
	{
		tex_y = (int)tex_pos & (engine->texture->height - 1);
		tex_pos += step;
		engine->color = mlx_get_argb_image_pixel(engine->texture, tex_x, tex_y);
		if (engine->color.a == 0)
			mlx_put_image_pixel(game->frame_3d, pixel, y, engine->color.argb);
		y++;
	}
}
