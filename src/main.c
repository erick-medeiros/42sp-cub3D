/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/30 16:52:27 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "window.h"

int	game_setup(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	mlx_clear_window(game->mlx, game->win);
	return (0);
}

int	game_loop(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, game);
	mlx_hook(game->win, DestroyNotify, NoEventMask, &mlx_loop_end, game->mlx);
	mlx_loop_hook(game->mlx, NULL, NULL);
	mlx_loop(game->mlx);
	return (0);
}

int	finish_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (0);
}

int	main(void)
{
	t_game	game;

	game_setup(&game);
	game_loop(&game);
	finish_game(&game);
}
