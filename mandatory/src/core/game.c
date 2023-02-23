/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:07:51 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/23 09:21:35 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "window.h"

void	game_init(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->canvas = NULL;
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->west_texture = NULL;
	game->east_texture = NULL;
	game->control.strafe_right = FALSE;
	game->control.strafe_left = FALSE;
	game->control.walk_up = FALSE;
	game->control.walk_down = FALSE;
	game->control.rotate_left = FALSE;
	game->control.rotate_right = FALSE;
	game->player.plane = create_vector(FOV_RAD, 0);
	game->player.pos = create_vector(0, 0);
	game->player.dir = create_vector(0, 0);
	game->player.movement = create_vector(0, 0);
	game->player.strafe = create_vector(0, 0);
	game->player.move_speed = MOVEMENT_SPEED;
	game->player.strafe_speed = STRAFE_SPEED;
	game->player.rotate_speed = 0;
}

int	game_setup(t_game *game)
{
	game_init(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (MLX_ERROR);
	game->win = mlx_new_window(game->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	if (!game->win)
		return (MLX_ERROR);
	game->canvas = create_canvas(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->canvas)
		return (MLX_ERROR);
	game->frame_3d = create_canvas(game->mlx,
			WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	if (!game->frame_3d)
		return (MLX_ERROR);
	game->player.pos = create_vector(5, 5);
	game->player.dir = create_vector(0, -1);
	mlx_do_key_autorepeatoff(game->mlx);
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

int	destroy_game(t_game *game)
{
	game->canvas = destroy_canvas(game->mlx, game->canvas);
	game->north_texture = destroy_canvas(game->mlx, game->north_texture);
	game->south_texture = destroy_canvas(game->mlx, game->south_texture);
	game->west_texture = destroy_canvas(game->mlx, game->west_texture);
	game->east_texture = destroy_canvas(game->mlx, game->east_texture);
	game->frame_3d = destroy_canvas(game->mlx, game->frame_3d);
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_do_key_autorepeaton(game->mlx);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	ft_free_matrix(game->map);
	game->map = NULL;
	return (0);
}
