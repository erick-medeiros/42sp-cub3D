/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:29:48 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 18:25:01 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	check_space_collision(t_game *game, t_vector new_pos)
{
	t_vector	collision;

	collision = create_vector(0, 0);
	if (new_pos.x - DIST_TO_WALL >= 0
		&& new_pos.x + DIST_TO_WALL < game->map_width)
		collision.x = 1;
	if (new_pos.y - DIST_TO_WALL >= 0
		&& new_pos.y + DIST_TO_WALL < game->map_height)
		collision.y = 1;
	return (collision);
}
