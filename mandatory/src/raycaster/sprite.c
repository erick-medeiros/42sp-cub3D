/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:39:18 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/11 16:48:01 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "config.h"
#include "raycaster.h"

t_img	*get_sprite_texture(t_sprite *sprite)
{
	t_img	*texture;

	texture = sprite->textures[sprite->num_texture];
	if (!texture)
	{
		sprite->num_texture = 0;
		return (get_sprite_texture(sprite));
	}
	if (sprite->frames == FRAMES_PER_SPRITE)
	{
		sprite->num_texture++;
		sprite->frames = 0;
	}
	else
		sprite->frames++;
	return (texture);
}

static t_vector	get_transform(t_game *game)
{
	t_vector	sprite_pos;
	t_vector	transform;

	sprite_pos.x = game->sprite.pos.x - game->player.pos.x;
	sprite_pos.y = game->sprite.pos.y - game->player.pos.y;
	transform.x = game->inverse_determinant * (game->player.dir.y
			* sprite_pos.x - game->player.dir.x * sprite_pos.y);
	transform.y = game->inverse_determinant * (-game->player.plane.y
			* sprite_pos.x + game->player.plane.x * sprite_pos.y);
	return (transform);
}

void	raycaster_sprites_draw(t_game *game, t_engine *engine,
	t_sprite_casting sc, int stripe)
{
	t_px	texture_pos;
	int		y;
	int		d;

	texture_pos.x = (256 * (stripe
				- (-sc.dimension.width / 2 + sc.dimension.x))
			* sc.texture->width / sc.dimension.width) / 256;
	if (sc.transform.y > 0 && stripe > 0 && stripe < engine->frame->width
		&& sc.transform.y < game->all_perpend[stripe])
	{
		y = sc.draw_start.y;
		while (y < sc.draw_end.y)
		{
			d = (y) * 256 - engine->frame->height * 128
				+ sc.dimension.height * 128;
			texture_pos.y = ((d * sc.texture->height)
					/ sc.dimension.height) / 256;
			mlx_copy_image_pixel(engine->frame, (t_px){stripe, y},
				sc.texture, texture_pos);
			y++;
		}
	}
}

void	raycaster_sprites(t_game *game, t_engine *engine)
{
	t_sprite_casting	sc;
	int					stripe;

	sc.transform = get_transform(game);
	sc.dimension.x = ((double)engine->frame->width / 2)
		* (1 + sc.transform.x / sc.transform.y);
	sc.dimension.width = fabs((engine->frame->height / (sc.transform.y)));
	sc.dimension.height = fabs((double)engine->frame->height
			/ (sc.transform.y));
	sc.draw_start.y = -sc.dimension.height / 2 + engine->frame->height / 2;
	sc.draw_end.y = sc.dimension.height / 2 + engine->frame->height / 2;
	sc.draw_start.x = -sc.dimension.width / 2 + sc.dimension.x;
	sc.draw_end.x = sc.dimension.width / 2 + sc.dimension.x;
	sc.draw_start.x = ft_constrain(sc.draw_start.x, 0,
			engine->frame->width - 1);
	sc.draw_start.y = ft_constrain(sc.draw_start.y, 0,
			engine->frame->height - 1);
	sc.draw_end.x = ft_constrain(sc.draw_end.x, 0, engine->frame->width - 1);
	sc.draw_end.y = ft_constrain(sc.draw_end.y, 0, engine->frame->height - 1);
	sc.texture = get_sprite_texture(&game->sprite);
	stripe = sc.draw_start.x - 1;
	while (++stripe < sc.draw_end.x)
		raycaster_sprites_draw(game, engine, sc, stripe);
}
