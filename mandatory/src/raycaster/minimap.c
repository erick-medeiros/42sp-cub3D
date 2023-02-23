/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:06:09 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/23 20:43:40 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"

void	init_minimap(t_game *game)
{
	t_rect	coord;

	coord.width = game->canvas->width * 0.10;
	coord.height = game->canvas->height * 0.20;
	coord.x = game->canvas->width - coord.width - 100;
	coord.y = 100;
	game->minimap.frame = create_canvas(game->mlx, coord.width, coord.height);
	game->minimap.scale = fmin((double)coord.width / game->map_width,
			(double)coord.height / game->map_height);
	game->minimap.pos = create_vector(coord.x, coord.y);
}

void	draw_minimap_ray(t_game *game, t_dda *dda, t_vector ray_dir)
{
	t_vector	start;
	t_vector	end;
	double		euclidian_dist;

	start = mult_vector_scalar(game->player.pos, game->minimap.scale);
	if (dda->hit_side == HIT_EAST || dda->hit_side == HIT_WEST)
		euclidian_dist = (fabs(dda->wall_hit.x - game->player.pos.x
					+ (((double)1 - dda->step_x) / 2))) * mag_vector(ray_dir)
			/ ray_dir.x;
	else
		euclidian_dist = (fabs(dda->wall_hit.y - game->player.pos.y
					+ (((double)1 - dda->step_y) / 2))) * mag_vector(ray_dir)
			/ ray_dir.y;
	end = ray_dir;
	end = set_mag_vector(ray_dir, fabs(euclidian_dist));
	end = mult_vector_scalar(end, game->minimap.scale);
	end = add_vector(end, start);
	draw_line(game->minimap.frame, start, end, 0xFF9F00);
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
	draw_rectangle(game->minimap.frame, coord, 0xFF0000);
	end = mult_vector_scalar(game->player.dir, minimap->scale);
	end = add_vector(start, end);
	draw_line(game->minimap.frame, start, end, 0xFF0000);
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
	draw_line(game->minimap.frame, p1, p2, 0x000000);
	draw_line(game->minimap.frame, p1, p3, 0x000000);
	draw_line(game->minimap.frame, p2, p4, 0x000000);
	draw_line(game->minimap.frame, p3, p4, 0x000000);
}

void	draw_minimap(t_game *game)
{
	t_rect	rect;
	int		x;
	int		y;

	draw_background(game->minimap.frame, 0xFF000000);
	x = 0;
	while (x < game->map_width)
	{
		y = 0;
		while (y < game->map_height)
		{
			rect.x = (x * game->minimap.scale);
			rect.y = (y * game->minimap.scale);
			rect.width = game->minimap.scale;
			rect.height = game->minimap.scale;
			if (game->map[y][x] == '1')
				draw_rectangle(game->minimap.frame, rect, 0xFAAFFF);
			else
				draw_rectangle(game->minimap.frame, rect, 0xFFFFFF);
			minimap_border(game, &rect);
			y++;
		}
		x++;
	}
	draw_player(game, &game->minimap);
}
