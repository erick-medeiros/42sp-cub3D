/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:33:39 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/07 10:11:26 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (pixel_y < rect.y + rect.height)
	{
		pixel_x = rect.x;
		while (pixel_x < rect.x + rect.width)
		{
			mlx_put_image_pixel(img, pixel_x, pixel_y, argb_color);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_texture_on_canvas(t_game *game, t_img *texture)
{
	t_argb	color;
	int		pixel_x;
	int		pixel_y;

	pixel_y = 0;
	while (pixel_y < texture->height)
	{
		pixel_x = 0;
		while (pixel_x < texture->width)
		{
			color = mlx_get_argb_image_pixel(texture, pixel_x, pixel_y);
			if (color.a == 0)
				mlx_put_image_pixel(game->canvas, pixel_x, pixel_y, color.argb);
			pixel_x++;
		}
		pixel_y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->canvas->ptr, 0, 0);
}
