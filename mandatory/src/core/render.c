/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:09:30 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/22 19:33:56 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"
#include "raycaster.h"

void	update_input(t_game *game)
{
	if (game->control.walk_up && !game->control.walk_down)
		walk_up_player(&game->player);
	if (game->control.walk_down && !game->control.walk_up)
		walk_down_player(&game->player);
	if (game->control.strafe_left && !game->control.strafe_right)
		strafe_left_player(&game->player);
	if (game->control.strafe_right && !game->control.strafe_left)
		strafe_right_player(&game->player);
	if (game->control.rotate_left && !game->control.rotate_right)
		rotate_player(&game->player, -game->player.speed);
	if (game->control.rotate_right && !game->control.rotate_left)
		rotate_player(&game->player, game->player.speed);
}

int	render(t_game *game)
{
	draw_background(game->canvas, 0x000000);
	update_input(game);
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
