/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 10:49:22 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/26 18:02:39 by frosa-ma         ###   ########.fr       */
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
	input_handler(&game->player, &game->control);
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
	input_handler(&game->player, &game->control);
	if (DEBUG)
		printf("keyrelease %d\n", keycode);
	return (1);
}

void	input_handler(t_player *player, t_control *control)
{
	if (control->walk_up && !control->walk_down)
		player->movement = mult_vector_scalar(player->dir, player->move_speed);
	else if (control->walk_down && !control->walk_up)
		player->movement = mult_vector_scalar(player->dir, -player->move_speed);
	else
		player->movement = create_vector(0, 0);
	if (control->strafe_left && !control->strafe_right)
		player->strafe = mult_vector_scalar(rotate_vector(player->dir, -M_PI_2),
				player->strafe_speed);
	else if (control->strafe_right && !control->strafe_left)
		player->strafe = mult_vector_scalar(rotate_vector(player->dir, M_PI_2),
				player->strafe_speed);
	else
		player->strafe = create_vector(0, 0);
	if (control->rotate_left && !control->rotate_right)
		player->rotate_speed = -ROTATE_SPEED_RAD;
	else if (control->rotate_right && !control->rotate_left)
		player->rotate_speed = ROTATE_SPEED_RAD;
	else
		player->rotate_speed = 0;
}
