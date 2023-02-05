/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:09:30 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/02 18:02:32 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_rect	get_ceiling_area(t_game *game)
{
	t_rect	rect;

	rect.x = 0;
	rect.y = 0;
	rect.width = game->canvas->width;
	rect.height = game->canvas->height / 2;
	return (rect);
}

static t_rect	get_floor_area(t_game *game)
{
	t_rect	rect;

	rect.x = 0;
	rect.y = game->canvas->height / 2;
	rect.width = game->canvas->width;
	rect.height = game->canvas->height;
	return (rect);
}

int	render(t_game *game)
{
	const t_rect	ceilling = get_ceiling_area(game);
	const t_rect	floor = get_floor_area(game);

	draw_rectangle(game->canvas, ceilling, game->ceilling_color.argb);
	draw_rectangle(game->canvas, floor, game->floor_color.argb);
	draw_texture_on_canvas(game, game->north_texture);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas->ptr, 0, 0);
	return (0);
}
