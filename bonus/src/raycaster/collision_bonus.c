/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:29:48 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 18:43:29 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_vector	check_door_range(t_game *game, t_vector pos, t_vector new_pos,
	t_vector map_pos)

{
	t_vector	collision;

	collision = create_vector(0, 0);
	if ((new_pos.x + DIST_TO_WALL < map_pos.x)
		|| (new_pos.x - DIST_TO_WALL > map_pos.x + 1)
		|| (pos.y + DIST_TO_WALL < map_pos.y)
		|| (pos.y - DIST_TO_WALL > map_pos.y + 1))
		collision.x = 1;
	if ((new_pos.y + DIST_TO_WALL < map_pos.y)
		|| (new_pos.y - DIST_TO_WALL > map_pos.y + 1)
		|| (pos.x + DIST_TO_WALL < map_pos.x)
		|| (pos.x - DIST_TO_WALL > map_pos.x + 1))
		collision.y = 1;
	game->door_range = 1;
	return (collision);
}

static t_vector	check_square(t_game *game, t_vector pos, t_vector new_pos,
	t_vector map_pos)
{
	t_vector	collision;

	collision = create_vector(0, 0);
	if (game->map[(int)map_pos.y][(int)map_pos.x] == '1')
	{
		if ((new_pos.x + DIST_TO_WALL < map_pos.x)
			|| (new_pos.x - DIST_TO_WALL > map_pos.x + 1)
			|| (pos.y + DIST_TO_WALL < map_pos.y)
			|| (pos.y - DIST_TO_WALL > map_pos.y + 1))
			collision.x = 1;
		if ((new_pos.y + DIST_TO_WALL < map_pos.y)
			|| (new_pos.y - DIST_TO_WALL > map_pos.y + 1)
			|| (pos.x + DIST_TO_WALL < map_pos.x)
			|| (pos.x - DIST_TO_WALL > map_pos.x + 1))
			collision.y = 1;
		return (collision);
	}
	if (game->map[(int)map_pos.y][(int)map_pos.x] == 'D')
		return (check_door_range(game, pos, new_pos, map_pos));
	return (create_vector(1, 1));
}

t_vector	check_collision(t_game *game, t_vector pos, t_vector new_pos,
	t_vector movement)
{
	t_vector	collision;
	t_vector	map_pos;

	collision = create_vector(1, 1);
	if (mag_vector(movement) > 0)
	{
		map_pos = create_vector(floor(pos.x), floor(pos.y));
		collision = mult_vector_vector(collision, check_square(game, pos,
					new_pos, create_vector(map_pos.x - 1, map_pos.y - 1)));
		collision = mult_vector_vector(collision, check_square(game, pos,
					new_pos, create_vector(map_pos.x - 1, map_pos.y)));
		collision = mult_vector_vector(collision, check_square(game, pos,
					new_pos, create_vector(map_pos.x - 1, map_pos.y + 1)));
		collision = mult_vector_vector(collision, check_square(game, pos,
					new_pos, create_vector(map_pos.x, map_pos.y - 1)));
		collision = mult_vector_vector(collision, check_square(game, pos,
					new_pos, create_vector(map_pos.x, map_pos.y + 1)));
		collision = mult_vector_vector(collision, check_square(game, pos,
					new_pos, create_vector(map_pos.x + 1, map_pos.y - 1)));
		collision = mult_vector_vector(collision, check_square(game, pos,
					new_pos, create_vector(map_pos.x + 1, map_pos.y)));
		collision = mult_vector_vector(collision, check_square(game, pos,
					new_pos, create_vector(map_pos.x + 1, map_pos.y + 1)));
	}
	return (collision);
}
