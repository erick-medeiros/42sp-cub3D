/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:30:12 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 18:01:07 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "cub3d.h"
#include "debug.h"
#include "feature_flags.h"
#include "minimap.h"

void	update_input(t_game *game, t_player *player)
{
	t_vector	movement;
	t_vector	new_pos;
	t_vector	collision;

	if (player->rotate_speed)
	{
		player->dir = rotate_vector(player->dir, player->rotate_speed);
		player->plane = rotate_vector(player->plane, player->rotate_speed);
	}
	movement = create_vector(0, 0);
	if (player->move_speed)
		movement = add_vector(movement,
				mult_vector_scalar(player->dir, player->move_speed));
	if (player->strafe_speed)
		movement = add_vector(movement,
				mult_vector_scalar(rotate_vector(player->dir, M_PI_2),
					player->strafe_speed));
	new_pos = add_vector(game->player.pos, movement);
	collision = check_space_collision(game, new_pos);
	movement = mult_vector_vector(movement, collision);
	game->player.pos = add_vector(game->player.pos, movement);
}

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

void	raycaster(t_game *game, t_img *img)
{
	t_engine	engine;
	int			pixel;

	update_input(game, &game->player);
	engine.frame = img;
	pixel = 0;
	while (pixel < img->width)
	{
		engine.ray_dir = raycaster_ray_dir(engine.frame, game->player, pixel);
		raycaster_perform_dda(game, &engine);
		game->animation.all_perpend[pixel] = engine.perp_wall_dist;
		raycaster_draw_line(game, &engine, pixel);
		pixel++;
	}
}
