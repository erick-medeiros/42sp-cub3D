/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:06:09 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/03 15:27:02 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

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
}

void	draw_minimap_ray(t_game *game, t_engine *engine, t_vector ray_dir)
{
	t_vector	start;
	t_vector	end;
	double		euclidian_dist;

	start = mult_vector_scalar(game->player.pos, game->minimap.scale);
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
	end = add_vector(end, start);
	draw_line(game->minimap.frame, start, end, MINIMAP_COLOR_RAY);
}

void	draw_player(t_game *game, t_minimap *minimap)
{
	t_rect		coord;
	t_vector	start;
	t_vector	end;

	start = mult_vector_scalar(game->player.pos, minimap->scale);
	coord.x = start.x - 3;
	coord.y = start.y - 3;
	coord.width = 6;
	coord.height = 6;
	draw_rectangle(game->minimap.frame, coord, MINIMAP_COLOR_PLAYER);
	end = mult_vector_scalar(game->player.dir, minimap->scale);
	end = add_vector(start, end);
	draw_line(game->minimap.frame, start, end, MINIMAP_COLOR_PLAYER);
}

static void	minimap_border(t_game *game, t_rect *rect)
{
	t_vector	p1;
	t_vector	p2;
	t_vector	p3;
	t_vector	p4;

	p1 = create_vector(rect->x, rect->y);
	p2 = create_vector(p1.x + rect->width, p1.y);
	p3 = create_vector(p1.x, p1.y + rect->height);
	p4 = create_vector(p1.x + rect->width, p1.y + rect->height);
	draw_line(game->minimap.frame, p1, p2, MINIMAP_COLOR_GRID);
	draw_line(game->minimap.frame, p1, p3, MINIMAP_COLOR_GRID);
	draw_line(game->minimap.frame, p2, p4, MINIMAP_COLOR_GRID);
	draw_line(game->minimap.frame, p3, p4, MINIMAP_COLOR_GRID);
}

void	draw_minimap(t_game *game)
{
	t_rect	rect;
	int		x;
	int		y;

	draw_background(game->minimap.frame, MINIMAP_COLOR_TRANSPARENT);
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
				draw_rectangle(game->minimap.frame, rect, MINIMAP_COLOR_WALL);
			else if (game->map[y][x] == '0')
				draw_rectangle(game->minimap.frame, rect, MINIMAP_COLOR_FLOOR);
			if (game->map[y][x] != ' ')
				minimap_border(game, &rect);
		}
	}
	draw_player(game, &game->minimap);
}
