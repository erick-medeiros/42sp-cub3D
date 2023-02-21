/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:32:57 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/21 09:53:05 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "debug.h"

double	calculate_scale(t_img *layer, double new_width, double new_height)
{
	double	scale;

	scale = fmin(new_width / layer->width, new_height / layer->height);
	return (scale);
}

void	draw_layer(t_game *game, t_img *layer, t_vector init, double scale)
{
	t_argb	color;
	int		pixel_x;
	int		pixel_y;
	t_rect	scaled_pixel;

	pixel_y = 0;
	while (pixel_y < layer->height)
	{
		pixel_x = 0;
		while (pixel_x < layer->width)
		{
			scaled_pixel.x = init.x + (pixel_x * scale);
			scaled_pixel.y = init.y + (pixel_y * scale);
			scaled_pixel.width = scale;
			scaled_pixel.height = scale;
			color = mlx_get_argb_image_pixel(layer, pixel_x, pixel_y);
			if (color.a == 0)
				draw_rectangle(game->canvas, scaled_pixel, color.argb);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_layer_fullscreen(t_game *game, t_img *layer)
{
	double	scale;

	scale = calculate_scale(layer, game->canvas->width, game->canvas->height);
	draw_layer(game, layer, (t_vector){0, 0}, scale);
}

void	draw_grid(t_img *canvas, t_img *layer, t_vector init, double scale)
{
	int			pixel_x;
	int			pixel_y;
	t_vector	p1;
	t_vector	p2;

	pixel_y = 0;
	while (pixel_y < layer->height)
	{
		pixel_x = 0;
		while (pixel_x < layer->width)
		{
			p1.x = init.x + (pixel_x * scale);
			p1.y = init.y + (pixel_y * scale);
			p2.x = p1.x + scale;
			p2.y = p1.y;
			draw_line(canvas, p1, p2, 0x000000);
			p2.x = p1.x;
			p2.y = p1.y + scale;
			draw_line(canvas, p1, p2, 0x000000);
			pixel_x++;
		}
		pixel_y++;
	}
}
