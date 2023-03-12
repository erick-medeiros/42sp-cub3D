/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:21:39 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 18:00:33 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	moviment_input(t_player *player, t_control *control)
{
	if (control->walk_up && !control->walk_down)
		player->move_speed = MOVEMENT_SPEED;
	else if (control->walk_down && !control->walk_up)
		player->move_speed = -MOVEMENT_SPEED;
	else
		player->move_speed = 0;
}

static void	strafe_input(t_player *player, t_control *control)
{
	if (control->strafe_left && !control->strafe_right)
		player->strafe_speed = -STRAFE_SPEED;
	else if (control->strafe_right && !control->strafe_left)
		player->strafe_speed = STRAFE_SPEED;
	else
		player->strafe_speed = 0;
}

static void	rotate_input(t_player *player, t_control *control)
{
	if (control->rotate_left && !control->rotate_right)
		player->rotate_speed = -ROTATE_SPEED_RAD;
	else if (control->rotate_right && !control->rotate_left)
		player->rotate_speed = ROTATE_SPEED_RAD;
	else
		player->rotate_speed = 0;
}

void	input_handler(t_game *game)
{
	rotate_input(&game->player, &game->control);
	moviment_input(&game->player, &game->control);
	strafe_input(&game->player, &game->control);
}
