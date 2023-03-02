/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:07:51 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/01 21:14:51 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "window.h"

int	game_setup(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (MLX_ERROR);
	game->win = mlx_new_window(game->mlx,
			game->window_width, game->window_height, WINDOW_NAME);
	if (!game->win)
		return (MLX_ERROR);
	game->canvas = create_canvas(game->mlx,
			game->window_width, game->window_height);
	if (!game->canvas)
		return (MLX_ERROR);
	game->frame_3d = create_canvas(game->mlx,
			game->window_width, game->window_height);
	if (!game->frame_3d)
		return (MLX_ERROR);
	game->player.pos = create_vector(5, 5);
	player_orientation(&game->player, 'N');
	mlx_do_key_autorepeatoff(game->mlx);
	draw_ceiling(game->frame_3d, game->ceilling_color.argb);
	draw_floor(game->frame_3d, game->floor_color.argb);
	save_canvas_background(game->frame_3d);
	init_textures(game);
	return (0);
}

int	game_loop(t_game *game)
{
	if (!game->mlx || !game->win || !game->canvas)
		return (MLX_ERROR);
	mlx_hook(game->win, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, &mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, &render, game);
	mlx_loop(game->mlx);
	return (0);
}
