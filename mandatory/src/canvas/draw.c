/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:33:39 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/23 10:06:09 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bresenham.h"
#include "cub3d.h"

void	draw_line(t_img *img, t_vector p1, t_vector p2, int color)
{
	t_bresenham	b;

	b.p1.x = p1.x;
	b.p1.y = p1.y;
	b.p2.x = p2.x;
	b.p2.y = p2.y;
	if (b.p1.x > b.p2.x || (b.p1.x == b.p2.x && b.p1.y > b.p2.y))
	{
		b.p1.x = p2.x;
		b.p1.y = p2.y;
		b.p2.x = p1.x;
		b.p2.y = p1.y;
	}
	b.delta_x = b.p2.x - b.p1.x;
	b.delta_y = b.p2.y - b.p1.y;
	if (b.delta_x == 0 || b.delta_y == 0 || abs(b.delta_x) == abs(b.delta_y))
		bresenham_axis(&b, img, color);
	else if ((abs(b.delta_x) > abs(b.delta_y)) && (b.delta_y > 0))
		bresenham_octante_1_5(&b, img, color);
	else if ((abs(b.delta_x) > abs(b.delta_y)) && (b.delta_y < 0))
		bresenham_octante_8_4(&b, img, color);
	else if ((abs(b.delta_x) < abs(b.delta_y)) && (b.delta_y > 0))
		bresenham_octante_2_6(&b, img, color);
	else if ((abs(b.delta_x) < abs(b.delta_y)) && (b.delta_y < 0))
		bresenham_octante_7_3(&b, img, color);
}

void	draw_background(t_img *img, int argb_color)
{
	int	pixel_x;
	int	pixel_y;

	pixel_y = 0;
	while (pixel_y < img->height)
	{
		pixel_x = 0;
		while (pixel_x < img->width)
		{
			mlx_put_image_pixel(img, pixel_x, pixel_y, argb_color);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_rectangle(t_img *img, t_rect rect, int argb_color)
{
	int	pixel_x;
	int	pixel_y;

	pixel_y = rect.y;
	while (pixel_y <= rect.y + rect.height)
	{
		pixel_x = rect.x;
		while (pixel_x <= rect.x + rect.width)
		{
			mlx_put_image_pixel(img, pixel_x, pixel_y, argb_color);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_ceiling(t_img *img, int argb_color)
{
	t_rect	rect;

	rect.x = 0;
	rect.y = 0;
	rect.width = img->width;
	rect.height = img->height / 2;
	draw_rectangle(img, rect, argb_color);
}

void	draw_floor(t_img *img, int argb_color)
{
	t_rect	rect;

	rect.x = 0;
	rect.y = img->height / 2;
	rect.width = img->width;
	rect.height = img->height;
	draw_rectangle(img, rect, argb_color);
}
