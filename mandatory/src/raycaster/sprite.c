/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:39:18 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 01:22:56 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "config.h"
#include "raycaster.h"

static t_vector	get_transform(t_game *game, t_sprite *sprite)
{
	t_vector	sprite_pos;
	t_vector	transform;

	sprite_pos.x = sprite->pos.x - game->player.pos.x;
	sprite_pos.y = sprite->pos.y - game->player.pos.y;
	transform.x = game->animation.inverse_determinant * (game->player.dir.y
			* sprite_pos.x - game->player.dir.x * sprite_pos.y);
	transform.y = game->animation.inverse_determinant * (-game->player.plane.y
			* sprite_pos.x + game->player.plane.x * sprite_pos.y);
	return (transform);
}

static void	raycaster_sprites_draw(t_game *game, t_engine *engine,
	t_sprite_casting sc, int stripe)
{
	t_px	texture_pos;
	int		y;
	int		d;

	texture_pos.x = (256 * (stripe
				- (-sc.dimension.width / 2 + sc.dimension.x))
			* sc.texture->width / sc.dimension.width) / 256;
	if (sc.transform.y > 0 && stripe > 0 && stripe < engine->frame->width
		&& sc.transform.y < game->animation.all_perpend[stripe])
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

static void	raycaster_sprite(t_game *game, t_engine *engine, t_sprite *sprite)
{
	t_sprite_casting	sc;
	int					stripe;

	sc.transform = get_transform(game, sprite);
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
	sc.texture = get_sprite_texture(sprite);
	stripe = sc.draw_start.x - 1;
	while (++stripe < sc.draw_end.x)
		raycaster_sprites_draw(game, engine, sc, stripe);
}

void	sort_sprites(int *sprite_order, int *sprite_distance, int amount)
{
	int	k;
	int	j;

	k = 1;
	while (k < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (sprite_distance[j] < sprite_distance[j + 1])
			{
				ft_swap(&sprite_distance[j], &sprite_distance[j + 1]);
				ft_swap(&sprite_order[j], &sprite_order[j + 1]);
			}
			j++;
		}
		k++;
	}
}

void	raycaster_sprites(t_game *game, t_engine *engine)
{
	int	i;

	if (game->animation.total_sprites == 0)
		return ;
	i = 0;
	while (i < game->animation.total_sprites)
	{
		game->animation.sprite_order[i] = i;
		game->animation.sprite_distance[i] = ((game->player.pos.x
					- game->animation.sprites[i].pos.x) * (game->player.pos.x
					- game->animation.sprites[i].pos.x) + (game->player.pos.y
					- game->animation.sprites[i].pos.y) * (game->player.pos.y
					- game->animation.sprites[i].pos.y));
		i++;
	}
	sort_sprites(game->animation.sprite_order,
		game->animation.sprite_distance, game->animation.total_sprites);
	i = 0;
	while (game->animation.sprites && game->animation.sprites[i].textures)
	{
		raycaster_sprite(game, engine,
			&game->animation.sprites[game->animation.sprite_order[i]]);
		i++;
	}
}
