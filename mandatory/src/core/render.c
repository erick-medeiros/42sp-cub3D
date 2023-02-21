/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:09:30 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/21 09:55:59 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"

int	render(t_game *game)
{
	draw_background(game->canvas, 0x000000);
	raycaster(game);
	draw_layer_fullscreen(game, game->frame_3d);
	if (FEATURE_FLAG_PENGUIN)
	{
		draw_background(game->canvas, 0x000000);
		draw_layer(game, game->north_texture, (t_vector){0, 0}, 1);
	}
	if (FEATURE_FLAG_RENDER_MAP)
		render_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas->ptr, 0, 0);
	return (0);
}
