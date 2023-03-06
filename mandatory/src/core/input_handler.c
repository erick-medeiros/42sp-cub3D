/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 19:21:39 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/06 19:24:57 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	moviment_input(t_player *player, t_control *control)
{
	if (control->walk_up && !control->walk_down)
		player->movement = mult_vector_scalar(player->dir, player->move_speed);
	else if (control->walk_down && !control->walk_up)
		player->movement = mult_vector_scalar(player->dir, -player->move_speed);
	else
		player->movement = create_vector(0, 0);
}

static void	strafe_input(t_player *player, t_control *control)
{
	if (control->strafe_left && !control->strafe_right)
		player->strafe = mult_vector_scalar(rotate_vector(player->dir, -M_PI_2),
				player->strafe_speed);
	else if (control->strafe_right && !control->strafe_left)
		player->strafe = mult_vector_scalar(rotate_vector(player->dir, M_PI_2),
				player->strafe_speed);
	else
		player->strafe = create_vector(0, 0);
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

void	input_handler(t_player *player, t_control *control)
{
	moviment_input(player, control);
	strafe_input(player, control);
	rotate_input(player, control);
}
