/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:30:12 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/27 19:07:16 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "cub3d.h"
#include "debug.h"
#include "feature_flags.h"

static t_vector	raycaster_ray_dir(t_img *img, t_player player, int pixel)
{
	double		mult;
	t_vector	camera_pixel;
	t_vector	ray_dir;

	mult = 2 * ((double)pixel / img->width) - 1;
	camera_pixel = mult_vector_scalar(player.plane, mult);
	ray_dir = add_vector(player.dir, camera_pixel);
	return (ray_dir);
}

t_img	*raycaster(t_game *game)
{
	t_engine	engine;
	int			pixel;

	pixel = 0;
	while (pixel < game->frame_3d->width)
	{
		engine.ray_dir = raycaster_ray_dir(game->frame_3d, game->player, pixel);
		raycaster_perform_dda(game, &engine);
		raycaster_draw_line(game, &engine, pixel);
		if (FEATURE_FLAG_MINIMAP)
			draw_minimap_ray(game, &engine, engine.ray_dir);
		pixel++;
	}
	return (game->frame_3d);
}
