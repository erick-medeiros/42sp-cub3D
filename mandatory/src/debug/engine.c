/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:53:46 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/28 16:57:33 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"
#include "debug.h"

void	debug_engine(t_engine *engine)
{
	debug_vector("ray_dir", engine->ray_dir);
	printf("delta_dist_x %lf\n", engine->delta_dist_x);
	printf("delta_dist_y %lf\n", engine->delta_dist_y);
	debug_vector("map_pos", engine->map_pos);
	printf("dist_to_side_x %lf\n", engine->dist_to_side_x);
	printf("dist_to_side_y %lf\n", engine->dist_to_side_y);
	printf("step_x %d\n", engine->step_x);
	printf("step_y %d\n", engine->step_y);
	printf("hit_side %d\n", engine->hit_side);
	debug_vector("wall_hit", engine->wall_hit);
	printf("perp_wall_dist %lf\n", engine->perp_wall_dist);
	printf("dda_line_size_x %lf\n", engine->dda_line_size_x);
	printf("dda_line_size_y %lf\n", engine->dda_line_size_y);
	printf("line_height %d\n", engine->line_height);
	printf("line_start %d\n", engine->line_start);
	printf("line_end %d\n", engine->line_end);
	printf("wall_hit_x %lf\n", engine->wall_hit_x);
}
