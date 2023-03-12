/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:09:45 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 18:44:42 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "raycaster_bonus.h"

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
	engine->line_height = 1 * engine->frame->height / engine->perp_wall_dist;
	height_mid = engine->frame->height / 2;
	engine->line_start = height_mid - engine->line_height / 2;
	engine->line_end = height_mid + engine->line_height / 2;
	if (engine->line_start < 0)
		engine->line_start = 0;
	if (engine->line_end >= engine->frame->height)
		engine->line_end = engine->frame->height - 1;
	if (engine->hit_side == HIT_X)
		engine->wall_hit_x = game->player.pos.y
			+ (engine->perp_wall_dist * engine->ray_dir.y);
	else
		engine->wall_hit_x = game->player.pos.x
			+ (engine->perp_wall_dist * engine->ray_dir.x);
	engine->wall_hit_x -= floor(engine->wall_hit_x);
}

void	raycaster_draw_line(t_game *game, t_engine *engine, int pixel)
{
	t_px	tex_px;
	t_px	frame_px;
	double	step;
	double	tex_pos;

	raycaster_get_texture_door(game, engine);
	raycaster_get_line(game, engine);
	tex_px.x = (int)(engine->wall_hit_x * engine->texture->width);
	if (engine->hit_side == HIT_X && engine->ray_dir.x > 0)
			tex_px.x = engine->texture->width - tex_px.x - 1;
	if (engine->hit_side == HIT_Y && engine->ray_dir.y < 0)
			tex_px.x = engine->texture->width - tex_px.x - 1;
	step = 1.0 * engine->texture->height / engine->line_height;
	tex_pos = (engine->line_start - (double)engine->frame->height / 2
			+ (double)engine->line_height / 2) * step;
	frame_px.x = pixel;
	frame_px.y = engine->line_start;
	while (frame_px.y < engine->line_end)
	{
		tex_px.y = (int)tex_pos & (engine->texture->height - 1);
		tex_pos += step;
		mlx_copy_image_pixel(engine->frame, frame_px, engine->texture, tex_px);
		frame_px.y++;
	}
}
