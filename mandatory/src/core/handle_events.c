/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 10:49:22 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 18:20:05 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "debug.h"

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
	if (DEBUG)
		printf("keyrelease %d\n", keycode);
	return (1);
}
