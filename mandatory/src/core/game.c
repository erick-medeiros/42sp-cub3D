/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:07:51 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/22 19:25:02 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "window.h"

static void	calculate_map_size(t_game *game)
{
	int	width;

	if (!game->map)
		return ;
	game->map_width = 0;
	game->map_height = 0;
	while (game->map[game->map_height])
	{
		width = 0;
		while (game->map[game->map_height][width])
			width++;
		if (game->map_width < width)
			game->map_width = width;
		game->map_height++;
	}
}

static void	game_init(t_game *game)
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
}

int	game_setup(t_game *game)
{
	game_init(game);
	calculate_map_size(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (MLX_ERROR);
	game->win = mlx_new_window(game->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	if (!game->win)
		return (MLX_ERROR);
	mlx_clear_window(game->mlx, game->win);
	game->canvas = create_canvas(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->canvas)
		return (MLX_ERROR);
	game->frame_3d = create_canvas(game->mlx,
			WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	if (!game->frame_3d)
		return (MLX_ERROR);
	game->player.plane = create_vector(0.66, 0);
	game->player.pos = create_vector(5, 5);
	game->player.dir = create_vector(0, -1);
	game->player.speed = 0.04;
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
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_do_key_autorepeaton(game->mlx);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	ft_free_matrix(game->map);
	return (0);
}
