/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 10:49:22 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/22 13:14:55 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "window.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == XKEY_ESC)
		mlx_loop_end(game->mlx);
	return (1);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == XKEY_ESC)
		mlx_loop_end(game->mlx);
	else if (keycode == XKEY_D)
		strafe_right_player(&game->player);
	else if (keycode == XKEY_A)
		strafe_left_player(&game->player);
	else if (keycode == XKEY_W)
		walk_up_player(&game->player);
	else if (keycode == XKEY_S)
		walk_down_player(&game->player);
	else if (keycode == XKEY_LEFT_ARROW)
		rotate_player(&game->player, -game->player.speed);
	else if (keycode == XKEY_RIGHT_ARROW)
		rotate_player(&game->player, game->player.speed);
	return (1);
}
