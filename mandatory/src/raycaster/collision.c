/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:29:48 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/09 16:56:05 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	check_collision(t_game *game, t_vector pos, t_vector movement)
{
	t_vector	collision;
	t_vector	new_pos;

	collision = create_vector(0, 0);
	new_pos = add_vector(pos, movement);
	if (new_pos.x >= 0 && new_pos.x < game->map_width)
		if (new_pos.y >= 0 && new_pos.y < game->map_height)
			return (new_pos);
	collision = pos;
	return (collision);
}
