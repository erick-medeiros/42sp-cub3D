/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 09:55:04 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 16:29:17 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"

static void	get_east(t_game *game, t_engine *engine)
{
	t_px	check;

	if (game->is_door)
		engine->texture = game->door_texture;
	else
	{
		game->door_range = 0;
		check.x = ft_constrain(engine->wall_hit.x - 1, 0, game->map_width - 1);
		check.y = engine->wall_hit.y;
		if (check.x != engine->wall_hit.x && game->map[check.y][check.x] == 'C')
			engine->texture = game->door_side_texture;
		else
			engine->texture = game->east_texture;
	}
}

static void	get_west(t_game *game, t_engine *engine)
{
	t_px	check;

	if (game->is_door)
		engine->texture = game->door_texture;
	else
	{
		game->door_range = 0;
		check.x = ft_constrain(engine->wall_hit.x + 1, 0, game->map_width - 1);
		check.y = engine->wall_hit.y;
		if (check.x != engine->wall_hit.x && game->map[check.y][check.x] == 'C')
			engine->texture = game->door_side_texture;
		else
			engine->texture = game->west_texture;
	}
}

static void	get_south(t_game *game, t_engine *engine)
{
	t_px	check;

	if (game->is_door)
		engine->texture = game->door_texture;
	else
	{
		game->door_range = 0;
		check.x = engine->wall_hit.x;
		check.y = ft_constrain(engine->wall_hit.y - 1, 0, game->map_height - 1);
		if (check.y != engine->wall_hit.y && game->map[check.y][check.x] == 'C')
			engine->texture = game->door_side_texture;
		else
			engine->texture = game->south_texture;
	}
}

static void	get_north(t_game *game, t_engine *engine)
{
	t_px	check;

	if (game->is_door)
		engine->texture = game->door_texture;
	else
	{
		game->door_range = 0;
		check.x = engine->wall_hit.x;
		check.y = ft_constrain(engine->wall_hit.y + 1, 0, game->map_height - 1);
		if (check.y != engine->wall_hit.y && game->map[check.y][check.x] == 'C')
			engine->texture = game->door_side_texture;
		else
			engine->texture = game->north_texture;
	}
}

void	raycaster_get_texture_door(t_game *game, t_engine *engine)
{
	if (engine->hit_side == HIT_X)
	{
		if (engine->step_x == 1)
			get_east(game, engine);
		else
			get_west(game, engine);
	}
	else
	{
		if (engine->step_y == 1)
			get_south(game, engine);
		else
			get_north(game, engine);
	}
}
