/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:09:30 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/21 14:30:12 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"
#include "raycaster.h"

int	render(t_game *game)
{
	draw_background(game->canvas, 0x000000);
	if (FEATURE_FLAG_MINIMAP)
		draw_minimap(game);
	raycaster(game);
	draw_layer_fullscreen(game, game->frame_3d);
	if (FEATURE_FLAG_MINIMAP)
		draw_layer(game, game->minimap.frame, game->minimap.pos);
	if (FEATURE_FLAG_PENGUIN)
	{
		draw_background(game->canvas, 0x000000);
		draw_layer(game, game->north_texture, (t_vector){0, 0});
	}
	mlx_put_image_to_window(game->mlx, game->win, game->canvas->ptr, 0, 0);
	return (0);
}
