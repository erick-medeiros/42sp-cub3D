/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:15:15 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/14 21:30:36 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*mlx_get_image_pixel(t_img *img, int x, int y)
{
	if (x < 0 || x >= img->width)
		return (NULL);
	if (y < 0 || y >= img->height)
		return (NULL);
	return (img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8)));
}

void	mlx_put_image_pixel(t_img *img, int x, int y, int argb_color)
{
	char	*pixel;
	char	byte_color;
	int		bytes;

	pixel = mlx_get_image_pixel(img, x, y);
	if (!pixel)
		return ;
	bytes = img->bits_per_pixel / 8;
	while (bytes-- > 0)
	{
		byte_color = (argb_color >> (bytes * 8)) & 0xFF;
		if (img->endian)
			*pixel++ = byte_color;
		else
			pixel[bytes] = byte_color;
	}
}

t_argb	mlx_get_argb_image_pixel(t_img *img, int x, int y)
{
	char	*pixel;
	int		argb[4];
	int		i;
	int		bytes;

	argb[0] = 0;
	argb[1] = 0;
	argb[2] = 0;
	argb[3] = 0;
	pixel = mlx_get_image_pixel(img, x, y);
	bytes = img->bits_per_pixel / 8;
	if (pixel)
	{
		i = 0;
		while (i < bytes)
		{
			if (img->endian)
				argb[4 - bytes + i] = pixel[i] & 0xFF;
			else
				argb[3 - i] = pixel[i] & 0xFF;
			++i;
		}
	}
	return (create_argb_color(argb[0], argb[1], argb[2], argb[3]));
}
