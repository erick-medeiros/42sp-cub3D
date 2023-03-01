/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:15:15 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/01 19:21:46 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_put_image_pixel(t_img *img, int x, int y, int argb_color)
{
	char	*pixel;
	char	byte_color;
	int		bytes;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	pixel = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
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

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (separate_argb_color(0));
	pixel = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	if (!pixel)
		return (separate_argb_color(0));
	ft_memset(&argb, 0, 4);
	bytes = img->bits_per_pixel / 8;
	i = 0;
	while (i < bytes)
	{
		if (img->endian)
			argb[4 - bytes + i] = pixel[i] & 0xFF;
		else
			argb[3 - i] = pixel[i] & 0xFF;
		++i;
	}
	return (create_argb_color(argb[0], argb[1], argb[2], argb[3]));
}

void	mlx_copy_image_pixel(t_img *dst, t_px dpx, t_img *src, t_px spx)
{
	int	*dst_pixel;
	int	*src_pixel;

	if (dpx.x < 0 || dpx.x >= dst->width || dpx.y < 0 || dpx.y >= dst->height)
		return ;
	if (spx.x < 0 || spx.x >= src->width || spx.y < 0 || spx.y >= src->height)
		return ;
	src_pixel = src->addr
		+ (spx.y * src->size_line + spx.x * (src->bits_per_pixel / 8));
	dst_pixel = dst->addr
		+ (dpx.y * dst->size_line + dpx.x * (dst->bits_per_pixel / 8));
	if (!dst_pixel || !src_pixel)
		return ;
	if (src->bits_per_pixel == 32)
	{
		if (src->endian && ((*src_pixel) & 0xFF) != 0)
			return ;
		else if (!src->endian && (((*src_pixel) >> 24) & 0xFF) != 0)
			return ;
	}
	*dst_pixel = *src_pixel;
}
