/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:09:30 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/10 15:24:24 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"

void	render_ceiling(t_game *game)
{
	t_rect	rect;

	rect.x = 0;
	rect.y = 0;
	rect.width = game->canvas->width;
	rect.height = game->canvas->height / 2;
	draw_rectangle(game->canvas, rect, game->ceilling_color.argb);
}

void	render_floor(t_game *game)
{
	t_rect	rect;

	rect.x = 0;
	rect.y = game->canvas->height / 2;
	rect.width = game->canvas->width;
	rect.height = game->canvas->height;
	draw_rectangle(game->canvas, rect, game->floor_color.argb);
}

int	render(t_game *game)
{
	render_ceiling(game);
	render_floor(game);
	draw_texture_on_canvas(game, game->north_texture);
	if (FEATURE_FLAG_RENDER_MAP)
		render_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas->ptr, 0, 0);
	return (0);
}
