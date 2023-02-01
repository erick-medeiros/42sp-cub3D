/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/31 21:18:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "window.h"

int	game_setup(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (MLX_ERROR);
	game->win = mlx_new_window(game->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	if (!game->win)
		return (MLX_ERROR);
	mlx_clear_window(game->mlx, game->win);
	if (init_mlx_image(game->mlx, &game->img, WINDOW_WIDTH, WINDOW_HEIGHT))
		return (MLX_ERROR);
	return (0);
}

int	render(t_game *game)
{
	const t_rect	ceilling = (t_rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2};
	const t_rect	floor = (t_rect){0, WINDOW_HEIGHT / 2, WINDOW_WIDTH,
		WINDOW_HEIGHT};

	draw_background(&game->img, 0xFFFFFF);
	draw_rectangle(&game->img, ceilling, 0xFF00FF);
	draw_rectangle(&game->img, floor, 0x00FFFF);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}

int	game_loop(t_game *game)
{
	if (!game->mlx || !game->win || !game->img.ptr)
		return (MLX_ERROR);
	mlx_hook(game->win, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, &mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, &render, game);
	mlx_loop(game->mlx);
	return (0);
}

int	finish_game(t_game *game)
{
	if (game->img.ptr)
		mlx_destroy_image(game->mlx, game->img.ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	return (0);
}

int	main(void)
{
	t_game	game;

	game_setup(&game);
	game_loop(&game);
	finish_game(&game);
}
