/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:56:13 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/02 09:51:09 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*create_canvas(void *mlx, int width, int height)
{
	t_img	*canvas;

	canvas = malloc(sizeof(*canvas));
	canvas->ptr = mlx_new_image(mlx, width, height);
	if (!canvas->ptr)
		return (destroy_canvas(mlx, canvas));
	canvas->addr = mlx_get_data_addr(canvas->ptr, &canvas->bits_per_pixel,
			&canvas->size_line, &canvas->endian);
	if (!canvas->addr)
		return (destroy_canvas(mlx, canvas));
	canvas->width = width;
	canvas->height = height;
	return (canvas);
}

t_img	*create_canvas_texture(void *mlx, char *filename)
{
	t_img	*texture;

	texture = malloc(sizeof(*texture));
	if (!texture)
		return (NULL);
	texture->ptr = mlx_xpm_file_to_image(mlx, filename,
			&texture->width, &texture->height);
	if (!texture->ptr)
		return (destroy_canvas(mlx, texture));
	texture->addr = mlx_get_data_addr(texture->ptr,
			&texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (!texture->addr)
		return (destroy_canvas(mlx, texture));
	return (texture);
}

void	*destroy_canvas(void *mlx, t_img *canvas)
{
	if (canvas)
	{
		if (mlx && canvas->ptr)
			mlx_destroy_image(mlx, canvas->ptr);
		free(canvas);
	}
	return (NULL);
}
