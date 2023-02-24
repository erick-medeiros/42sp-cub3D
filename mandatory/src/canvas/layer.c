/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:32:57 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/23 20:12:35 by eandre-f         ###   ########.fr       */
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

void	draw_layer(t_img *canvas, t_img *layer, t_vector init)
{
	t_argb	color;
	int		pixel_x;
	int		pixel_y;

	pixel_y = 0;
	while (pixel_y < layer->height)
	{
		pixel_x = 0;
		while (pixel_x < layer->width)
		{
			color = mlx_get_argb_image_pixel(layer, pixel_x, pixel_y);
			if (color.a == 0)
				mlx_put_image_pixel(canvas,
					init.x + pixel_x, init.y + pixel_y, color.argb);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_layer_scale(t_img *canvas, t_img *layer, t_vector init,
	double scale)
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
				draw_rectangle(canvas, scaled_pixel, color.argb);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_layer_fullscreen(t_img *canvas, t_img *layer)
{
	double	scale;

	scale = calculate_scale(layer, canvas->width, canvas->height);
	draw_layer_scale(canvas, layer, create_vector(0, 0), scale);
}
