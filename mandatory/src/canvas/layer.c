/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 01:32:57 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/03 16:07:58 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "debug.h"

void	draw_layer(t_img *canvas, t_img *layer,
	t_px start_canvas, t_px start_layer)
{
	t_px	layer_px;
	t_px	canvas_px;
	t_px	px;

	px.y = 0;
	while (px.y + start_layer.y < layer->height
		&& px.y + start_canvas.y < canvas->height)
	{
		px.x = 0;
		while (px.x + start_layer.x < layer->width
			&& px.x + start_canvas.x < canvas->width)
		{
			layer_px.x = px.x + start_layer.x;
			layer_px.y = px.y + start_layer.y;
			canvas_px.x = px.x + start_canvas.x;
			canvas_px.y = px.y + start_canvas.y;
			mlx_copy_image_pixel(canvas, canvas_px, layer, layer_px);
			px.x++;
		}
		px.y++;
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
	while (pixel_y < layer->height && pixel_y < canvas->height)
	{
		pixel_x = 0;
		while (pixel_x < layer->width && pixel_x < canvas->width)
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

	scale = fmin((double)canvas->width / layer->width,
			(double)canvas->height / layer->height);
	draw_layer_scale(canvas, layer, create_vector(0, 0), scale);
}
