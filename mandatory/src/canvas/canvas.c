/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:56:13 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/01 20:03:41 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*create_canvas(void *mlx, int width, int height)
{
	t_img	*canvas;

	canvas = malloc(sizeof(*canvas));
	canvas->ptr = mlx_new_image(mlx, width, height);
	if (!canvas->ptr)
	{
		free(canvas);
		return (NULL);
	}
	canvas->addr = mlx_get_data_addr(canvas->ptr, &canvas->bits_per_pixel,
			&canvas->size_line, &canvas->endian);
	if (!canvas->addr)
	{
		mlx_destroy_image(mlx, canvas->ptr);
		free(canvas);
		return (NULL);
	}
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
	{
		free(texture);
		return (NULL);
	}
	texture->addr = mlx_get_data_addr(texture->ptr,
			&texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (!texture->addr)
	{
		mlx_destroy_image(mlx, texture->ptr);
		free(texture);
		return (NULL);
	}
	return (texture);
}
