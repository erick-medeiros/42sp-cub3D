/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:15:15 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/31 20:23:56 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx_image(void *mlx, t_mlx_img *img, int width, int height)
{
	img->ptr = mlx_new_image(mlx, width, height);
	if (!img->ptr)
		return (MLX_ERROR);
	img->addr = mlx_get_data_addr(img->ptr, &img->bits_per_pixel,
			&img->size_line, &img->endian);
	img->width = width;
	img->height = height;
	return (0);
}

char	*mlx_get_image_pixel(t_mlx_img *img, int x, int y)
{
	return (img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8)));
}

void	mlx_put_image_pixel(t_mlx_img *img, int x, int y, int argb_color)
{
	char	*pixel;
	char	byte_color;
	int		bytes;

	if (x < 0 || x >= img->width)
		return ;
	if (y < 0 || y >= img->height)
		return ;
	pixel = mlx_get_image_pixel(img, x, y);
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
