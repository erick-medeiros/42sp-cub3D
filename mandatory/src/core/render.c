/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:09:30 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/02 09:54:02 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(t_game *game)
{
	const t_rect	ceilling = (t_rect){
		0, 0, game->canvas->width, game->canvas->height / 2
	};
	const t_rect	floor = (t_rect){
		0, game->canvas->height / 2, game->canvas->width, game->canvas->height
	};

	draw_rectangle(game->canvas, ceilling, game->ceilling_color.argb);
	draw_rectangle(game->canvas, floor, game->floor_color.argb);
	draw_texture_on_canvas(game, game->north_texture);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas->ptr, 0, 0);
	return (0);
}
