/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:32:00 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/22 13:30:03 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	walk_up_player(t_player *player)
{
	t_vector	walk;

	walk = mult_vector_scalar(player->dir, player->speed);
	player->pos = add_vector(player->pos, walk);
}

void	walk_down_player(t_player *player)
{
	t_vector	walk;

	walk = mult_vector_scalar(player->dir, player->speed);
	player->pos = sub_vector(player->pos, walk);
}

void	strafe_left_player(t_player *player)
{
	t_vector	strafe;

	strafe = player->dir;
	strafe = rotate_vector(strafe, -M_PI_2);
	strafe = mult_vector_scalar(strafe, player->speed);
	player->pos = add_vector(player->pos, strafe);
}

void	strafe_right_player(t_player *player)
{
	t_vector	strafe;

	strafe = player->dir;
	strafe = rotate_vector(strafe, M_PI_2);
	strafe = mult_vector_scalar(strafe, player->speed);
	player->pos = add_vector(player->pos, strafe);
}

void	rotate_player(t_player *player, double angle_radian)
{
	player->dir = rotate_vector(player->dir, angle_radian);
	player->plane = rotate_vector(player->plane, angle_radian);
}
