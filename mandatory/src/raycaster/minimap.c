/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:06:09 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/03 16:53:14 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void	minimap_border(t_img *frame, t_rect *rect)
{
	t_vector	p1;
	t_vector	p2;
	t_vector	p3;
	t_vector	p4;

	p1 = create_vector(rect->x, rect->y);
	p2 = create_vector(p1.x + rect->width, p1.y);
	p3 = create_vector(p1.x, p1.y + rect->height);
	p4 = create_vector(p1.x + rect->width, p1.y + rect->height);
	draw_line(frame, p1, p2, MINIMAP_COLOR_GRID);
	draw_line(frame, p1, p3, MINIMAP_COLOR_GRID);
	draw_line(frame, p2, p4, MINIMAP_COLOR_GRID);
	draw_line(frame, p3, p4, MINIMAP_COLOR_GRID);
}

static void	draw_map_2d(t_game *game, t_img *frame)
{
	t_rect	rect;
	int		x;
	int		y;

	draw_background(frame, MINIMAP_COLOR_TRANSPARENT);
	x = -1;
	while (++x < game->map_width)
	{
		y = -1;
		while (++y < game->map_height)
		{
			rect.x = (x * game->minimap.scale);
			rect.y = (y * game->minimap.scale);
			rect.width = game->minimap.scale;
			rect.height = game->minimap.scale;
			if (game->map[y][x] == '1')
				draw_rectangle(frame, rect, MINIMAP_COLOR_WALL);
			else if (game->map[y][x] != ' ')
				draw_rectangle(frame, rect, MINIMAP_COLOR_FLOOR);
			if (game->map[y][x] != ' ')
				minimap_border(frame, &rect);
		}
	}
}

void	init_minimap(t_game *game)
{
	t_rect	coord;
	double	edge_distance;

	coord.width = game->canvas->width * 0.15;
	coord.height = game->canvas->height * 0.15;
	edge_distance = fmin(coord.width * 0.15, coord.height * 0.15);
	coord.x = game->canvas->width - coord.width - edge_distance;
	coord.y = edge_distance;
	game->minimap.frame = create_canvas(game->mlx, coord.width, coord.height);
	game->minimap.scale = 15;
	game->minimap.pos = create_vector(coord.x, coord.y);
	game->minimap.map_2d = create_canvas(game->mlx,
			game->map_width * game->minimap.scale,
			game->map_height * game->minimap.scale);
	draw_map_2d(game, game->minimap.map_2d);
	draw_background(game->minimap.frame, MINIMAP_COLOR_TRANSPARENT);
	save_canvas_background(game->minimap.frame);
	game->minimap.middle_frame.x = (double)game->minimap.frame->width / 2;
	game->minimap.middle_frame.y = (double)game->minimap.frame->height / 2;
	game->minimap.fullscreen = TRUE;
}

void	draw_minimap_ray(t_game *game, t_engine *engine, t_vector ray_dir)
{
	t_vector	start;
	t_vector	end;
	double		euclidian_dist;

	if (engine->hit_side == HIT_X)
		euclidian_dist = (fabs(engine->wall_hit.x - game->player.pos.x
					+ (((double)1 - engine->step_x) / 2))) * mag_vector(ray_dir)
			/ ray_dir.x;
	else
		euclidian_dist = (fabs(engine->wall_hit.y - game->player.pos.y
					+ (((double)1 - engine->step_y) / 2))) * mag_vector(ray_dir)
			/ ray_dir.y;
	end = ray_dir;
	end = set_mag_vector(ray_dir, fabs(euclidian_dist));
	end = mult_vector_scalar(end, game->minimap.scale);
	start.x = game->minimap.middle_frame.x;
	start.y = game->minimap.middle_frame.y;
	end = add_vector(end, start);
	draw_line(game->minimap.frame, start, end, MINIMAP_COLOR_RAY);
}

void	draw_minimap(t_game *game)
{
	t_vector	scaled_player;
	t_px		map_2d_px;
	t_rect		player;
	t_vector	center;
	t_vector	dir;

	reset_canvas(game->minimap.frame);
	scaled_player = mult_vector_scalar(game->player.pos, game->minimap.scale);
	map_2d_px.x = scaled_player.x - game->minimap.middle_frame.x;
	map_2d_px.y = scaled_player.y - game->minimap.middle_frame.y;
	draw_layer(game->minimap.frame, game->minimap.map_2d,
		(t_px){0, 0}, map_2d_px);
	center.x = game->minimap.middle_frame.x;
	center.y = game->minimap.middle_frame.y;
	player.x = game->minimap.middle_frame.x - 3;
	player.y = game->minimap.middle_frame.y - 3;
	player.width = 6;
	player.height = 6;
	draw_rectangle(game->minimap.frame, player, MINIMAP_COLOR_PLAYER);
	dir = add_vector(center,
			mult_vector_scalar(game->player.dir, game->minimap.scale));
	draw_line(game->minimap.frame, center, dir, MINIMAP_COLOR_PLAYER);
}
