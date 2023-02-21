/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:30:12 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/21 10:02:19 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "debug.h"
#include <stdbool.h>
#include "feature_flags.h"

#define FPS_FOV 0.66

enum e_hit
{
	HIT_NORTH,
	HIT_SOUTH,
	HIT_EAST,
	HIT_WEST
};

typedef struct e_dda
{
	double		delta_dist_x;
	double		delta_dist_y;
	t_vector	map_pos;
	double		dist_to_side_x;
	double		dist_to_side_y;
	int			step_x;
	int			step_y;
	int			hit_side;
}	t_dda;

typedef struct s_ray_line
{
	int	start_y;
	int	end_y;
	int	hit_side;
}	t_ray_line;

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
	draw_line(game->canvas,
		((t_vector){coord.x, coord.y}),
		((t_vector){dir.x, dir.y}),
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
	scale = calculate_scale(game->_minimap, coord.width, coord.height);
	draw_layer(game, game->_minimap,
		(t_vector){coord.x, coord.y}, scale);
	draw_grid(game->canvas, game->_minimap,
		(t_vector){coord.x, coord.y}, scale);
	draw_player(game, coord, scale);
}

t_vector	raycaster_get_ray_dir(t_img *img, t_player player, int pixel)
{
	double		mult;
	t_vector	camera_pixel;
	t_vector	ray_dir;

	mult = 2 * ((double)pixel / img->width) - 1;
	camera_pixel = mult_vector_scalar(player.plane, mult);
	ray_dir = add_vector(player.dir, camera_pixel);
	return (ray_dir);
}

t_dda	raycaster_dda_variables(t_player player, t_vector ray_dir)
{
	t_dda	dda;

	if (ray_dir.x == 0)
	{
		dda.delta_dist_x = 1;
		dda.delta_dist_y = 0;
	}
	else if (ray_dir.y)
		dda.delta_dist_x = fabs(1 / ray_dir.x);
	if (ray_dir.y == 0)
	{
		dda.delta_dist_x = 0;
		dda.delta_dist_y = 1;
	}
	else if (ray_dir.x)
		dda.delta_dist_y = fabs(1 / ray_dir.y);
	dda.map_pos = create_vector((int)player.pos.x, (int)player.pos.y);
	if (ray_dir.x < 0)
	{
		dda.dist_to_side_x = (player.pos.x - dda.map_pos.x) * dda.delta_dist_x;
		dda.step_x = -1;
	}
	else
	{
		dda.dist_to_side_x = (dda.map_pos.x + 1 - player.pos.x)
			* dda.delta_dist_x;
		dda.step_x = 1;
	}
	if (ray_dir.y < 0)
	{
		dda.dist_to_side_y = (player.pos.y - dda.map_pos.y) * dda.delta_dist_y;
		dda.step_y = -1;
	}
	else
	{
		dda.dist_to_side_y = (dda.map_pos.y + 1 - player.pos.y)
			* dda.delta_dist_y;
		dda.step_y = 1;
	}
	return (dda);
}

t_vector	raycaster_run_dda(t_game *game, t_dda *dda)
{
	int			hit;
	double		dda_line_size_x;
	double		dda_line_size_y;
	t_vector	wall_map_pos;

	hit = 0;
	dda_line_size_x = dda->dist_to_side_x;
	dda_line_size_y = dda->dist_to_side_y;
	wall_map_pos = dda->map_pos;
	while (hit == 0)
	{
		if (dda_line_size_x < dda_line_size_y)
		{
			wall_map_pos.x += dda->step_x;
			dda_line_size_x += dda->delta_dist_x;
			if (dda->step_x == 1)
				dda->hit_side = HIT_EAST;
			else
				dda->hit_side = HIT_WEST;
		}
		else
		{
			wall_map_pos.y += dda->step_y;
			dda_line_size_y += dda->delta_dist_y;
			if (dda->step_y == 1)
				dda->hit_side = HIT_SOUTH;
			else
				dda->hit_side = HIT_NORTH;
		}
		if (game->map[(int)wall_map_pos.x][(int)wall_map_pos.y] == '1')
			hit = 1;
	}
	return (wall_map_pos);
}

t_ray_line	raycaster_get_line(t_game *game, t_vector wall, t_dda dda,
		t_vector ray_dir)
{
	t_ray_line	line;
	double		perpendicular_dist;
	double		wall_line_height;

	if (dda.hit_side == HIT_EAST || dda.hit_side == HIT_WEST)
		perpendicular_dist = fabs(wall.x - game->player.pos.x
				+ (((double)1 - dda.step_x) / 2)) / ray_dir.x;
	else
		perpendicular_dist = fabs(wall.y - game->player.pos.y
				+ (((double)1 - dda.step_y) / 2)) / ray_dir.y;
	wall_line_height = game->frame_3d->height / perpendicular_dist;
	line.start_y = ((double)game->frame_3d->height / 2) - (wall_line_height / 2);
	line.end_y = ((double)game->frame_3d->height / 2) + (wall_line_height / 2);
	return (line);
}

void	raycaster_draw(t_game *game, t_ray_line line, int pixel, t_dda dda)
{
	double	color;

	color = 0x000000;
	if (dda.hit_side == HIT_EAST)
		color = 0x0000FF;
	else if (dda.hit_side == HIT_WEST)
		color = 0xFF0000;
	else if (dda.hit_side == HIT_SOUTH)
		color = 0x00FF00;
	else if (dda.hit_side == HIT_NORTH)
		color = 0xFFFF00;
	draw_line(game->frame_3d,
		((t_vector){pixel, line.start_y}),
		((t_vector){pixel, line.end_y}),
		color);
}

t_img	*raycaster(t_game *game)
{
	int			pixel;
	t_vector	ray_dir;
	t_dda		dda;
	t_vector	wall;
	t_ray_line	line;

	draw_background(game->canvas, 0x000000);
	draw_background(game->frame_3d, game->floor_color.argb);
	draw_rectangle(game->frame_3d,
		(t_rect){0, 0, game->frame_3d->width, game->frame_3d->height / 2},
		game->ceilling_color.argb);
	pixel = 0;
	while (pixel < game->frame_3d->width)
	{
		ray_dir = raycaster_get_ray_dir(game->frame_3d, game->player, pixel);
		dda = raycaster_dda_variables(game->player, ray_dir);
		wall = raycaster_run_dda(game, &dda);
		line = raycaster_get_line(game, wall, dda, ray_dir);
		raycaster_draw(game, line, pixel, dda);
		pixel++;
	}
	return (game->frame_3d);
}
