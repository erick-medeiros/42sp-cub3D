/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:30:12 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/16 18:50:28 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>
#include "feature_flags.h"

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

void	canvas_remap(t_img *img, t_img *remap, t_rect coord, bool border)
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
}

void	draw_minimap(t_game *game)
{
	int		x;
	int		y;
	t_rect	coord;

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
	coord.x = 10;
	coord.y = 0;
	coord.width = game->canvas->width * 0.45;
	coord.height = game->canvas->height;
	canvas_remap(game->canvas, game->_minimap, coord, true);
}

void	draw_engine(t_game *game)
{
	t_rect	coord;

	coord.x = game->canvas->width / 2;
	coord.y = 0;
	coord.width = game->canvas->width / 2 - 10;
	coord.height = game->canvas->height;
	draw_background(game->_engine, 0x00FFFF);
	canvas_remap(game->canvas, game->_engine, coord, false);
}

void	raycaster(t_game *game)
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;

	draw_background(game->canvas, 0x000000);
	pos = create_vector(5, 5);
	dir = create_vector(0, -1);
	plane = create_vector(FPS_FOV, 0);
	(void)pos;
	(void)dir;
	(void)plane;
	draw_minimap(game);
	draw_engine(game);
}
