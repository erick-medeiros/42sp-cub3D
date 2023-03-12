/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:07:51 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 18:00:13 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	draw_ceiling(game->canvas, game->ceilling_color.argb);
	draw_floor(game->canvas, game->floor_color.argb);
	save_canvas_background(game->canvas);
	init_textures(game);
	game->control.fov_ratio = tanf(FOV_RAD / (game->canvas->width - 1));
	game->animation.all_perpend = ft_calloc(game->canvas->width,
			sizeof(double));
	game->animation.inverse_determinant = 1.0 / (game->player.plane.x
			* game->player.dir.y - game->player.dir.x * game->player.plane.y);
	return (0);
}

int	game_loop(t_game *game)
{
	if (!game->mlx || !game->win || !game->canvas)
		return (MLX_ERROR);
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_hook(game->win, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, &mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, &render, game);
	mlx_loop(game->mlx);
	mlx_do_key_autorepeaton(game->mlx);
	return (0);
}
