/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:33:39 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/31 20:43:28 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_mlx_img *img, int argb_color)
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

void	draw_rectangle(t_mlx_img *img, t_rect rect, int argb_color)
{
	int	pixel_x;
	int	pixel_y;

	pixel_y = rect.y;
	while (pixel_y < rect.height)
	{
		pixel_x = rect.x;
		while (pixel_x < rect.width)
		{
			mlx_put_image_pixel(img, pixel_x, pixel_y, argb_color);
			pixel_x++;
		}
		pixel_y++;
	}
}
