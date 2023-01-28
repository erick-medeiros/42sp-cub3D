/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/27 23:55:41 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "window.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == X_KEY_ESC)
		mlx_loop_end(game->mlx);
	return (1);
}

void	game_loop(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	mlx_clear_window(game->mlx, game->win);
	mlx_hook(game->win, X_KEYPRESS, X_KEYPRESSMASK, &handle_keypress, game);
	mlx_hook(game->win, X_DESTROYNOTIFY, 0, &mlx_loop_end, game->mlx);
	mlx_loop(game->mlx);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

int	main(void)
{
	t_game	game;

	game_loop(&game);
}
