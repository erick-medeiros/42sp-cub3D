/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:56:13 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 17:32:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_img	*create_canvas(void *mlx, int width, int height)
{
	t_img	*img;

	img = malloc(sizeof(*img));
	if (!img)
		return (NULL);
	img->width = width;
	img->height = height;
	img->background = NULL;
	img->ptr = mlx_new_image(mlx, width, height);
	if (!img->ptr)
		return (destroy_canvas(mlx, img));
	img->addr = mlx_get_data_addr(img->ptr,
			&img->bytes_per_pixel, &img->size_line, &img->endian);
	if (!img->addr)
		return (destroy_canvas(mlx, img));
	img->bytes_per_pixel = img->bytes_per_pixel / 8;
	img->size = img->width * img->height * img->bytes_per_pixel;
	img->alpha_mask = 0;
	if (img->bytes_per_pixel == 4 && img->endian)
		img->alpha_mask = 0xFF;
	else if (img->bytes_per_pixel == 4 && !img->endian)
		img->alpha_mask = 0xFF000000;
	return (img);
}

t_img	*create_canvas_texture(void *mlx, char *filename)
{
	t_img	*img;

	img = malloc(sizeof(*img));
	if (!img)
		return (NULL);
	img->background = NULL;
	img->ptr = mlx_xpm_file_to_image(mlx, filename, &img->width, &img->height);
	if (!img->ptr)
		return (destroy_canvas(mlx, img));
	img->addr = mlx_get_data_addr(img->ptr,
			&img->bytes_per_pixel, &img->size_line, &img->endian);
	if (!img->addr)
		return (destroy_canvas(mlx, img));
	img->bytes_per_pixel = img->bytes_per_pixel / 8;
	img->size = img->width * img->height * img->bytes_per_pixel;
	img->alpha_mask = 0;
	if (img->bytes_per_pixel == 4 && img->endian)
		img->alpha_mask = 0xFF;
	else if (img->bytes_per_pixel == 4 && !img->endian)
		img->alpha_mask = 0xFF000000;
	return (img);
}

void	save_canvas_background(t_img *canvas)
{
	canvas->background = ft_calloc(sizeof(char), canvas->size);
	ft_memcpy(canvas->background, canvas->addr, canvas->size);
}

void	reset_canvas(t_img *canvas)
{
	if (canvas->background)
		ft_memcpy(canvas->addr, canvas->background, canvas->size);
	else
		ft_memset(canvas->addr, 0, canvas->size);
}

void	*destroy_canvas(void *mlx, t_img *canvas)
{
	if (canvas)
	{
		if (mlx && canvas->ptr)
			mlx_destroy_image(mlx, canvas->ptr);
		if (canvas->background)
			free(canvas->background);
		free(canvas);
	}
	return (NULL);
}
