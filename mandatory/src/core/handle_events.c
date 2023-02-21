/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 10:49:22 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/21 03:54:49 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "window.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		mlx_loop_end(game->mlx);
	return (1);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		mlx_loop_end(game->mlx);
	else if (keycode == 97)
		strafe_right_player(&game->player);
	else if (keycode == 100)
		strafe_left_player(&game->player);
	else if (keycode == 119)
		walk_up_player(&game->player);
	else if (keycode == 115)
		walk_down_player(&game->player);
	else if (keycode == 65361)
		rotate_player(&game->player, -game->player.speed);
	else if (keycode == 65363)
		rotate_player(&game->player, game->player.speed);
	return (1);
}
