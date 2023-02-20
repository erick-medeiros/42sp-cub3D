/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:30:12 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/19 21:03:50 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "debug.h"
#include <stdbool.h>
#include "feature_flags.h"
#include "bresenham.h"

#define FPS_FOV 0.66
#define IMAGE_PIXELS 320

void	canvas_remap_border(t_img *img, t_rect rect, double scale)
{
	rect.height = 1;
	draw_rectangle(img, rect, 0x000000);
	rect.width = 1;
	rect.height = scale;
	draw_rectangle(img, rect, 0x000000);
}

double	canvas_remap(t_img *img, t_img *remap, t_rect coord, bool border)
{
	double	scale;
	int		pixel_x;
	int		pixel_y;
	t_rect	rect;
	t_argb	color;

	scale = fmin((double)coord.width / remap->width,
			(double)coord.height / remap->height);
	pixel_x = -1;
	while (++pixel_x < remap->width)
	{
		pixel_y = -1;
		while (++pixel_y < remap->height)
		{
			rect.x = coord.x + (pixel_x * scale);
			rect.y = coord.y + (pixel_y * scale);
			rect.width = scale;
			rect.height = scale;
			color = mlx_get_argb_image_pixel(remap, pixel_x, pixel_y);
			if (color.a == 0)
				draw_rectangle(img, rect, color.argb);
			if (border)
				canvas_remap_border(img, rect, scale);
		}
	}
	return (scale);
}

void	draw_player(t_game *game, t_rect coord, double scale)
{
	t_vector	dir;

	coord.x += game->player.pos.x * scale;
	coord.y += game->player.pos.y * scale;
	coord.width = 5;
	coord.height = coord.width;
	draw_rectangle(game->canvas, coord, 0xFF0000);
	dir = add_vector(game->player.pos, game->player.dir);
	dir = mult_vector_scalar(dir, scale);
	bresenham(game->canvas,
		&((t_point){coord.x, coord.y}),
		&((t_point){dir.x, dir.y}),
		0xFF0000);
}

void	draw_minimap(t_game *game)
{
	int		x;
	int		y;
	t_rect	coord;
	double	scale;

	draw_background(game->canvas, 0x000000);
	x = 0;
	while (x < game->_minimap->width)
	{
		y = 0;
		while (y < game->_minimap->height)
		{
			if (game->map[y][x] == '1')
				mlx_put_image_pixel(game->_minimap, x, y, 0xFAAFFF);
			else
				mlx_put_image_pixel(game->_minimap, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
	coord.x = 0;
	coord.y = 0;
	coord.width = game->canvas->width * 0.45;
	coord.height = game->canvas->height;
	scale = canvas_remap(game->canvas, game->_minimap, coord, true);
	draw_player(game, coord, scale);
}

void	draw_engine(t_game *game)
{
	t_rect	coord;

	coord.x = game->canvas->width / 2;
	coord.y = 0;
	coord.width = game->canvas->width / 2 - 10;
	coord.height = game->canvas->height;
	canvas_remap(game->canvas, game->_engine, coord, false);
}

void	raycaster(t_game *game)
{
	int			pixel;
	t_vector	camera_pixel;
	t_vector	ray_dir;
	double		mult;
	double		delta_dist_x;
	double		delta_dist_y;
	t_vector	map_pos;
	double		dist_to_side_x;
	double		dist_to_side_y;
	int			step_x;
	int			step_y;

	game->player.dir = rotate_vector(game->player.dir, -0.03);
	game->player.plane = rotate_vector(game->player.plane, -0.03);
	draw_background(game->canvas, 0x000000);
	draw_background(game->_engine, 0x000000);
	pixel = 0;
	while (pixel < game->_engine->width)
	{
		mult = 2 * ((double)pixel / game->_engine->width) - 1;
		camera_pixel = mult_vector_scalar(game->player.plane, mult);
		ray_dir = add_vector(game->player.dir, camera_pixel);
		if (ray_dir.x == 0)
		{
			delta_dist_x = 1;
			delta_dist_y = 0;
		}
		else if (ray_dir.y)
			delta_dist_x = fabs(1 / ray_dir.x);
		if (ray_dir.y == 0)
		{
			delta_dist_x = 0;
			delta_dist_y = 1;
		}
		else if (ray_dir.x)
			delta_dist_y = fabs(1 / ray_dir.y);
		map_pos = create_vector((int)game->player.pos.x, (int)game->player.pos.y);
		if (ray_dir.x < 0)
		{
			dist_to_side_x = (game->player.pos.x - map_pos.x) * delta_dist_x;
			step_x = -1;
		}
		else
		{
			dist_to_side_x = (map_pos.x + 1 - game->player.pos.x) * delta_dist_x;
			step_x = 1;
		}
		if (ray_dir.y < 0)
		{
			dist_to_side_y = (game->player.pos.y - map_pos.y) * delta_dist_y;
			step_y = -1;
		}
		else
		{
			dist_to_side_y = (map_pos.y + 1 - game->player.pos.y) * delta_dist_y;
			step_y = 1;
		}
		int	hit = 0;
		double dda_line_size_x = dist_to_side_x;
		double dda_line_size_y = dist_to_side_y;
		t_vector	wall_map_pos = map_pos;
		int	hit_side;
		double perpendicularDist;
		while (hit == 0)
		{
			if (dda_line_size_x < dda_line_size_y)
			{
				wall_map_pos.x += step_x;
				dda_line_size_x += delta_dist_x;
				if (step_x == 1)
					hit_side = 1;
				else
					hit_side = 2;
			}
			else
			{
				wall_map_pos.y += step_y;
				dda_line_size_y += delta_dist_y;
				if (step_y == 1)
					hit_side = 3;
				else
					hit_side = 4;
			}
			if (game->map[(int)wall_map_pos.x][(int)wall_map_pos.y] == '1')
				hit = 1;
		}
		if (hit_side == 1 || hit_side == 2)
			perpendicularDist = fabs(wall_map_pos.x - game->player.pos.x + (((double)1 - step_x) / 2)) / ray_dir.x;
		else
			perpendicularDist = fabs(wall_map_pos.y - game->player.pos.y + (((double)1 - step_y) / 2)) / ray_dir.y;
		
		double wall_line_height = game->_engine->height / perpendicularDist;

		int line_start_y = ((double)game->_engine->height / 2) - (wall_line_height / 2);
		int line_end_y = ((double)game->_engine->height / 2) + (wall_line_height / 2);
		double color;
		color = 0x000000;
		if (hit_side == 1)
			color = 0x0000FF;
		else if (hit_side == 2)
			color = 0xFF0000;
		else if (hit_side == 3)
			color = 0x00FF00;
		else if (hit_side == 4)
			color = 0xFFFF00;
		bresenham(game->_engine,
			&((t_point){pixel, line_start_y}),
			&((t_point){pixel, line_end_y}),
			color);
		pixel++;
	}
	draw_minimap(game);
	draw_engine(game);
}
