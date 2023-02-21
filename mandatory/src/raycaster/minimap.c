/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:06:09 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/21 10:08:38 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_game *game, t_rect coord, double scale)
{
	t_vector	dir;

	coord.x += game->player.pos.x * scale;
	coord.y += game->player.pos.y * scale;
	coord.width = 5;
	coord.height = coord.width;
	draw_rectangle(game->canvas, coord, 0xFF0000);
	dir = add_vector(game->player.pos, game->player.dir);
	dir = mult_vector_scalar(dir, scale);
	draw_line(game->canvas,
		((t_vector){coord.x, coord.y}),
		((t_vector){dir.x, dir.y}),
		0xFF0000);
}

t_img	*raycaster_minimap(t_game *game)
{
	int	x;
	int	y;

	draw_background(game->canvas, 0x000000);
	x = 0;
	while (x < game->_minimap->width)
	{
		y = 0;
		while (y < game->_minimap->height)
		{
			if (game->map[y][x] == '1')
				mlx_put_image_pixel(game->_minimap, x, y, 0xFAAFFF);
			else
				mlx_put_image_pixel(game->_minimap, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
	return (game->_minimap);
}

void	draw_minimap(t_game *game)
{
	t_rect	coord;
	double	scale;

	coord.x = 0;
	coord.y = 0;
	coord.width = game->canvas->width * 0.45;
	coord.height = game->canvas->height;
	scale = calculate_scale(game->_minimap, coord.width, coord.height);
	draw_layer(game, game->_minimap,
		(t_vector){coord.x, coord.y}, scale);
	draw_grid(game->canvas, game->_minimap,
		(t_vector){coord.x, coord.y}, scale);
	draw_player(game, coord, scale);
}
