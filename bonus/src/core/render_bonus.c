/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:09:30 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 17:35:07 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "feature_flags_bonus.h"
#include "raycaster_bonus.h"
#include "debug_bonus.h"

int	render(t_game *game)
{
	input_handler(game);
	reset_canvas(game->canvas);
	raycaster(game, game->canvas);
	if (FEATURE_FLAG_MINIMAP && game->minimap.frame)
	{
		if (game->minimap.fullscreen)
			draw_layer(game->canvas, game->minimap.frame_fullscreen,
				game->minimap.pos_fullscreen, (t_px){0, 0});
		else
			draw_layer(game->canvas, game->minimap.frame,
				game->minimap.pos, (t_px){0, 0});
	}
	mlx_put_image_to_window(game->mlx, game->win, game->canvas->ptr, 0, 0);
	if (FEATURE_FLAG_FPS)
		fps_meter(game->mlx, -1);
	return (0);
}