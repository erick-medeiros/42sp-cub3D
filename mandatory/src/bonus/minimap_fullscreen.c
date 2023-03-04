/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fullscreen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:51:31 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/04 14:53:32 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

void	draw_fullscreen_minimap(t_game *game)
{
	t_vector	scaled_player;
	t_rect		player;
	t_vector	dir;

	reset_canvas(game->minimap.frame_fullscreen);
	scaled_player = mult_vector_scalar(game->player.pos,
			game->minimap.scale);
	scaled_player = mult_vector_scalar(scaled_player,
			game->minimap.scale_fullscreen);
	scaled_player.x += game->minimap.start_map_in_fullscreen.x;
	scaled_player.y += game->minimap.start_map_in_fullscreen.y;
	player.x = scaled_player.x - 3;
	player.y = scaled_player.y - 3;
	player.width = 6;
	player.height = 6;
	draw_rectangle(game->minimap.frame_fullscreen,
		player, MINIMAP_COLOR_PLAYER);
	dir = mult_vector_scalar(game->player.dir, game->minimap.scale);
	dir = mult_vector_scalar(dir, game->minimap.scale_fullscreen);
	dir = add_vector(scaled_player, dir);
	draw_line(game->minimap.frame_fullscreen,
		scaled_player, dir, MINIMAP_COLOR_PLAYER);
}
