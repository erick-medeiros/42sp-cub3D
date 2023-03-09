/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:07:51 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/09 19:52:41 by eandre-f         ###   ########.fr       */
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
	return (0);
}

int	game_loop(t_game *game)
{
	if (!game->mlx || !game->win || !game->canvas)
		return (MLX_ERROR);
	mlx_do_key_autorepeatoff(game->mlx);
	if (game->config.mouse)
	{
		mlx_mouse_hide(game->mlx, game->win);
		mlx_hook(game->win, MotionNotify, PointerMotionMask,
			&handle_mouse_move, game);
		mlx_hook(game->win, ButtonPress, ButtonPressMask,
			&handle_mouse_press, game);
		mlx_hook(game->win, ButtonRelease, ButtonReleaseMask,
			&handle_mouse_release, game);
	}
	mlx_hook(game->win, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, &mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, &render, game);
	mlx_loop(game->mlx);
	mlx_do_key_autorepeaton(game->mlx);
	if (game->config.mouse)
		mlx_mouse_show(game->mlx, game->win);
	return (0);
}
