/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:25:39 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/21 10:41:00 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"

static void	dda_calcule_delta_dist(t_dda *dda, t_vector ray_dir)
{
	if (ray_dir.x == 0)
	{
		dda->delta_dist_x = 1;
		dda->delta_dist_y = 0;
	}
	else if (ray_dir.y)
		dda->delta_dist_x = fabs(1 / ray_dir.x);
	if (ray_dir.y == 0)
	{
		dda->delta_dist_x = 0;
		dda->delta_dist_y = 1;
	}
	else if (ray_dir.x)
		dda->delta_dist_y = fabs(1 / ray_dir.y);
}

static void	dda_calcule_dist_to_side(t_dda *dda, t_player player,
	t_vector ray_dir)
{
	if (ray_dir.x < 0)
	{
		dda->dist_to_side_x = (player.pos.x - dda->map_pos.x)
			* dda->delta_dist_x;
		dda->step_x = -1;
	}
	else
	{
		dda->dist_to_side_x = (dda->map_pos.x + 1 - player.pos.x)
			* dda->delta_dist_x;
		dda->step_x = 1;
	}
	if (ray_dir.y < 0)
	{
		dda->dist_to_side_y = (player.pos.y - dda->map_pos.y)
			* dda->delta_dist_y;
		dda->step_y = -1;
	}
	else
	{
		dda->dist_to_side_y = (dda->map_pos.y + 1 - player.pos.y)
			* dda->delta_dist_y;
		dda->step_y = 1;
	}
}

t_dda	raycaster_dda_variables(t_player player, t_vector ray_dir)
{
	t_dda	dda;

	dda_calcule_delta_dist(&dda, ray_dir);
	dda.map_pos = create_vector((int)player.pos.x, (int)player.pos.y);
	dda_calcule_dist_to_side(&dda, player, ray_dir);
	return (dda);
}

static	void	dda_loop(t_vector *wall_map_pos, t_dda *dda,
	double *dda_line_size_x, double *dda_line_size_y)
{
	if (*dda_line_size_x < *dda_line_size_y)
	{
		wall_map_pos->x += dda->step_x;
		*dda_line_size_x += dda->delta_dist_x;
		dda->hit_side = HIT_WEST;
		if (dda->step_x == 1)
			dda->hit_side = HIT_EAST;
	}
	else
	{
		wall_map_pos->y += dda->step_y;
		*dda_line_size_y += dda->delta_dist_y;
		dda->hit_side = HIT_NORTH;
		if (dda->step_y == 1)
			dda->hit_side = HIT_SOUTH;
	}
}

t_vector	raycaster_run_dda(t_game *game, t_dda *dda)
{
	int			hit;
	double		dda_line_size_x;
	double		dda_line_size_y;
	t_vector	wall_map_pos;

	hit = 0;
	dda_line_size_x = dda->dist_to_side_x;
	dda_line_size_y = dda->dist_to_side_y;
	wall_map_pos = dda->map_pos;
	while (hit == 0)
	{
		dda_loop(&wall_map_pos, dda, &dda_line_size_x, &dda_line_size_y);
		if (game->map[(int)wall_map_pos.x][(int)wall_map_pos.y] == '1')
			hit = 1;
	}
	return (wall_map_pos);
}
