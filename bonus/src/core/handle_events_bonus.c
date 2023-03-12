/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 10:49:22 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 17:35:07 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "debug_bonus.h"
#include "feature_flags_bonus.h"
#include "door_bonus.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == XKEY_ESC)
		mlx_loop_end(game->mlx);
	else if (keycode == XKEY_W)
		game->control.walk_up = TRUE;
	else if (keycode == XKEY_S)
		game->control.walk_down = TRUE;
	else if (keycode == XKEY_A)
		game->control.strafe_left = TRUE;
	else if (keycode == XKEY_D)
		game->control.strafe_right = TRUE;
	else if (keycode == XKEY_LEFT_ARROW)
		game->control.rotate_left = TRUE;
	else if (keycode == XKEY_RIGHT_ARROW)
		game->control.rotate_right = TRUE;
	else if (FEATURE_FLAG_DOOR && keycode == XKEY_SPACE)
	{
		if (game->door_range)
			open_door_and_update_matrix(game);
		else if (is_door_open(game))
			close_door_and_update_matrix(game);
	}
	if (DEBUG)
		printf("keypress %d\n", keycode);
	return (1);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == XKEY_ESC)
		mlx_loop_end(game->mlx);
	else if (keycode == XKEY_W)
		game->control.walk_up = FALSE;
	else if (keycode == XKEY_S)
		game->control.walk_down = FALSE;
	else if (keycode == XKEY_A)
		game->control.strafe_left = FALSE;
	else if (keycode == XKEY_D)
		game->control.strafe_right = FALSE;
	else if (keycode == XKEY_LEFT_ARROW)
		game->control.rotate_left = FALSE;
	else if (keycode == XKEY_RIGHT_ARROW)
		game->control.rotate_right = FALSE;
	else if (keycode == XKEY_M)
		game->minimap.fullscreen = !game->minimap.fullscreen;
	else if (FEATURE_FLAG_DOOR && keycode == XKEY_SPACE)
		if (game->door_range)
			open_door_and_update_matrix(game);
	if (DEBUG)
		printf("keyrelease %d\n", keycode);
	return (1);
}

int	handle_mouse_move(int x, int y, t_game *game)
{
	game->control.mouse.x = game->control.mouse.x
		- game->canvas->width / 2 + x;
	game->control.mouse.y = game->control.mouse.y
		- game->canvas->height / 2 + y;
	mlx_mouse_move(game->mlx, game->win,
		game->canvas->width / 2, game->canvas->height / 2);
	if (DEBUG)
		printf("mouse move x %d y %d\n", x, y);
	return (0);
}

int	handle_mouse_press(int button, int x, int y, t_game *game)
{
	(void)game;
	if (DEBUG)
		printf("mouse press button %d x %d y %d\n", button, x, y);
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_game *game)
{
	(void)game;
	if (DEBUG)
		printf("mouse release button %d x %d y %d\n", button, x, y);
	return (0);
}
