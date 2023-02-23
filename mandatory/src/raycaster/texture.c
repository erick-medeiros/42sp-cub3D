/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:09:45 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/21 10:16:14 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"

void	raycaster_draw_line(t_game *game, t_vector start, t_vector end,
			int hit_side)
{
	double	color;

	color = 0x000000;
	if (hit_side == HIT_EAST)
		color = 0x0000FF;
	else if (hit_side == HIT_WEST)
		color = 0xFF0000;
	else if (hit_side == HIT_SOUTH)
		color = 0x00FF00;
	else if (hit_side == HIT_NORTH)
		color = 0xFFFF00;
	draw_line(game->frame_3d, start, end, color);
}