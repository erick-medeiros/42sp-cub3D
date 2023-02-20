/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 10:49:22 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/19 21:04:34 by eandre-f         ###   ########.fr       */
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
		game->player.pos.x = game->player.pos.x - 0.1;
	else if (keycode == 100)
		game->player.pos.x = game->player.pos.x + 0.1;
	else if (keycode == 119)
		game->player.pos.y = game->player.pos.y - 0.1;
	else if (keycode == 115)
		game->player.pos.y = game->player.pos.y + 0.1;
	else if (keycode == 65361)
	{
		game->player.dir = rotate_vector(game->player.dir, -0.1);
		game->player.plane = rotate_vector(game->player.plane, -0.1);
	}
	else if (keycode == 65363)
	{
		game->player.dir = rotate_vector(game->player.dir, 0.1);
		game->player.plane = rotate_vector(game->player.plane, 0.1);
	}
	return (1);
}
