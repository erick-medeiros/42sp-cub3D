/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:25:39 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 18:09:46 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"
#include "feature_flags.h"

static void	dda_calcule_delta_dist(t_engine *engine)
{
	if (engine->ray_dir.x == 0)
	{
		engine->delta_dist_x = 1;
		engine->delta_dist_y = 0;
	}
	else if (engine->ray_dir.y)
		engine->delta_dist_x = fabs(1 / engine->ray_dir.x);
	if (engine->ray_dir.y == 0)
	{
		engine->delta_dist_x = 0;
		engine->delta_dist_y = 1;
	}
	else if (engine->ray_dir.x)
		engine->delta_dist_y = fabs(1 / engine->ray_dir.y);
}

static void	dda_calcule_dist_to_side(t_engine *engine, t_player player)
{
	engine->map_pos = create_vector((int)player.pos.x, (int)player.pos.y);
	if (engine->ray_dir.x < 0)
	{
		engine->dist_to_side_x = (player.pos.x - engine->map_pos.x)
			* engine->delta_dist_x;
		engine->step_x = -1;
	}
	else
	{
		engine->dist_to_side_x = (engine->map_pos.x + 1 - player.pos.x)
			* engine->delta_dist_x;
		engine->step_x = 1;
	}
	if (engine->ray_dir.y < 0)
	{
		engine->dist_to_side_y = (player.pos.y - engine->map_pos.y)
			* engine->delta_dist_y;
		engine->step_y = -1;
	}
	else
	{
		engine->dist_to_side_y = (engine->map_pos.y + 1 - player.pos.y)
			* engine->delta_dist_y;
		engine->step_y = 1;
	}
}

static void	assign_wall_hit_x_and_y(t_game *game, t_engine *engine)
{
	engine->wall_hit.x = fmin(engine->wall_hit.x, game->map_width - 1);
	engine->wall_hit.x = fmax(engine->wall_hit.x, 0);
	engine->wall_hit.y = fmin(engine->wall_hit.y, game->map_height - 1);
	engine->wall_hit.y = fmax(engine->wall_hit.y, 0);
}

static int	check_hit(t_game *game, t_engine *engine)
{
	int	hit;

	hit = 0;
	if (engine->wall_hit.y < 0 || engine->wall_hit.y >= game->map_height)
		hit = 1;
	if (engine->wall_hit.x < 0 || engine->wall_hit.x >= game->map_width)
		hit = 1;
	if (hit == 0)
	{
		if (game->map[(int)engine->wall_hit.y][(int)engine->wall_hit.x] == '1')
			hit = 1;
		if (game->map[(int)engine->wall_hit.y][(int)engine->wall_hit.x] == ' ')
			hit = 1;
	}
	if (hit)
		assign_wall_hit_x_and_y(game, engine);
	return (hit);
}

void	raycaster_perform_dda(t_game *game, t_engine *engine)
{
	double	hit;

	dda_calcule_delta_dist(engine);
	dda_calcule_dist_to_side(engine, game->player);
	engine->dda_line_size_x = engine->dist_to_side_x;
	engine->dda_line_size_y = engine->dist_to_side_y;
	engine->wall_hit = engine->map_pos;
	hit = 0;
	while (hit == 0)
	{
		if (engine->dda_line_size_x < engine->dda_line_size_y)
		{
			engine->wall_hit.x += engine->step_x;
			engine->dda_line_size_x += engine->delta_dist_x;
			engine->hit_side = HIT_X;
		}
		else
		{
			engine->wall_hit.y += engine->step_y;
			engine->dda_line_size_y += engine->delta_dist_y;
			engine->hit_side = HIT_Y;
		}
		hit = check_hit(game, engine);
	}
}
