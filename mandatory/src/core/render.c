/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:09:30 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/23 17:22:21 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"
#include "raycaster.h"

void	update_input(t_player *player)
{
	player->pos = add_vector(player->pos, player->movement);
	player->pos = add_vector(player->pos, player->strafe);
	if (player->rotate_speed)
	{
		player->dir = rotate_vector(player->dir, player->rotate_speed);
		player->plane = rotate_vector(player->plane, player->rotate_speed);
	}
}

int	render(t_game *game)
{
	update_input(&game->player);
	if (FEATURE_FLAG_MINIMAP)
		draw_minimap(game);
	reset_canvas(game->frame_3d);
	raycaster(game);
	if (FEATURE_FLAG_MINIMAP)
		draw_layer(game, game->minimap.frame, game->minimap.pos);
	if (FEATURE_FLAG_PENGUIN)
	{
		draw_background(game->canvas, 0x000000);
		draw_layer(game, game->north_texture, (t_vector){0, 0});
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame_3d->ptr, 0, 0);
	return (0);
}
