/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:30:12 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/15 11:30:31 by eandre-f         ###   ########.fr       */
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

void	canvas_remap(t_img *img, t_img *remap, bool border)
{
	double	scale;
	int		pixel_x;
	int		pixel_y;
	t_rect	rect;
	t_argb	color;

	scale = fmin((double)img->width / remap->width,
			(double)img->height / remap->height);
	pixel_x = -1;
	while (++pixel_x < remap->width)
	{
		pixel_y = -1;
		while (++pixel_y < remap->height)
		{
			rect.x = pixel_x * scale;
			rect.y = pixel_y * scale;
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

void	draw_map(t_img *img)
{
	const char	gamemap[RAYCASTER_MAP_BLOCK][RAYCASTER_MAP_BLOCK] = {
		"1111111111", "1100100011", "1000000001", "1000000001", "1000000001",
		"1100000011", "1000000001", "1000000001", "1100100011", "1111111111"
	};
	int			x;
	int			y;

	x = 0;
	while (x < RAYCASTER_MAP_BLOCK)
	{
		y = 0;
		while (y < RAYCASTER_MAP_BLOCK)
		{
			if (gamemap[y][x] == '1')
				mlx_put_image_pixel(img, x, y, 0xFAAFFF);
			else
				mlx_put_image_pixel(img, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
}

void	raycaster(t_game *game)
{
	t_img		*img_map;
	t_img		*img_screen;
	t_vector	pos;
	t_vector	dir;

	img_map = game->west_texture;
	img_screen = game->south_texture;
	draw_background(game->canvas, 0x000000);
	draw_background(img_screen, 0x00FFFF);
	draw_background(img_map, 0x000FFF);
	pos = create_vector(5, 5);
	dir = create_vector(0, -1);
	(void)pos;
	(void)dir;
	draw_map(img_map);
	canvas_remap(img_screen, img_map, true);
	canvas_remap(game->canvas, img_screen, false);
}
