/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:30:12 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/23 10:07:20 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "cub3d.h"
#include "feature_flags.h"

t_vector	raycaster_get_ray_dir(t_img *img, t_player player, int pixel)
{
	double		mult;
	t_vector	camera_pixel;
	t_vector	ray_dir;

	mult = 2 * ((double)pixel / img->width) - 1;
	camera_pixel = mult_vector_scalar(player.plane, mult);
	ray_dir = add_vector(player.dir, camera_pixel);
	return (ray_dir);
}

t_ray_line	raycaster_get_line(t_game *game, t_dda dda, t_vector ray_dir)
{
	t_ray_line	line;
	double		perpendicular_dist;
	double		wall_line_height;
	double		height_mid;

	if (dda.hit_side == HIT_EAST || dda.hit_side == HIT_WEST)
		perpendicular_dist = fabs(dda.wall_hit.x - game->player.pos.x
				+ (((double)1 - dda.step_x) / 2)) / ray_dir.x;
	else
		perpendicular_dist = fabs(dda.wall_hit.y - game->player.pos.y
				+ (((double)1 - dda.step_y) / 2)) / ray_dir.y;
	wall_line_height = game->frame_3d->height / perpendicular_dist;
	height_mid = ((double)game->frame_3d->height / 2);
	line.start_y = height_mid - (wall_line_height / 2);
	line.end_y = height_mid + (wall_line_height / 2);
	return (line);
}

t_img	*raycaster(t_game *game)
{
	int			pixel;
	t_vector	ray_dir;
	t_dda		dda;
	t_ray_line	line;

	pixel = 0;
	while (pixel < game->frame_3d->width)
	{
		ray_dir = raycaster_get_ray_dir(game->frame_3d, game->player, pixel);
		dda = raycaster_dda_variables(game->player, ray_dir);
		dda.wall_hit = raycaster_run_dda(game, &dda);
		line = raycaster_get_line(game, dda, ray_dir);
		raycaster_draw_line(game,
			((t_vector){pixel, line.start_y}),
			((t_vector){pixel, line.end_y}), dda.hit_side);
		if (FEATURE_FLAG_MINIMAP)
			draw_minimap_ray(game, &dda, ray_dir);
		pixel++;
	}
	return (game->frame_3d);
}
