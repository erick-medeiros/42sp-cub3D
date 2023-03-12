/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/11 22:39:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"
#include "parser.h"
#include "minimap.h"

#define FOX1 "./assets/fox/t/b1.xpm"
#define FOX2 "./assets/fox/t/b2.xpm"
#define FOX3 "./assets/fox/t/b3.xpm"
#define FOX4 "./assets/fox/t/b4.xpm"
#define FOX5 "./assets/fox/t/b5.xpm"
#define FOX6 "./assets/fox/t/b6.xpm"
#define FOX7 "./assets/fox/t/b7.xpm"

void	configure_sprite(void *mlx, t_sprite *sprite)
{
	sprite->textures = ft_calloc(8, sizeof(t_img *));
	sprite->textures[0] = create_canvas_texture(mlx, FOX1);
	sprite->textures[1] = create_canvas_texture(mlx, FOX2);
	sprite->textures[2] = create_canvas_texture(mlx, FOX3);
	sprite->textures[3] = create_canvas_texture(mlx, FOX4);
	sprite->textures[4] = create_canvas_texture(mlx, FOX5);
	sprite->textures[5] = create_canvas_texture(mlx, FOX6);
	sprite->textures[6] = create_canvas_texture(mlx, FOX7);
	sprite->num_texture = 0;
	sprite->frames = 0;
	sprite->pos = create_vector(0, 0);
}

t_sprite	*configure_animation(t_game *game, void *mlx)
{
	t_sprite	*sprites;
	int			total;

	total = 2;
	game->animation.total_sprites = total;
	sprites = ft_calloc(total + 1, sizeof(t_sprite));
	configure_sprite(mlx, &(sprites[0]));
	sprites[0].pos = create_vector(5.5, 4.5);
	configure_sprite(mlx, &(sprites[1]));
	sprites[1].pos = create_vector(3.5, 3.5);
	game->animation.sprite_order = ft_calloc(total, sizeof(int));
	game->animation.sprite_distance = ft_calloc(total, sizeof(int));
	return (sprites);
}

void	destroy_sprite(void *mlx, t_sprite *sprites, t_animation *animation)
{
	int	i;

	i = 0;
	while (sprites && sprites[i].textures)
	{
		sprites[i].num_texture = 0;
		while (sprites[i].textures
			&& sprites[i].textures[sprites[i].num_texture])
		{
			sprites[i].textures[sprites[i].num_texture] = destroy_canvas(mlx,
					sprites[i].textures[sprites[i].num_texture]);
			sprites[i].num_texture++;
		}
		free(sprites[i].textures);
		i++;
	}
	free(sprites);
	free(animation->sprite_order);
	free(animation->sprite_distance);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	game_init(&game);
	if (!input_validation(&game, argc, argv))
	{
		clean_params(&game.params);
		return (1);
	}
	if (!init_map(&game, argv))
	{
		clean_params(&game.params);
		return (1);
	}
	game_setup(&game);
	game.animation.sprites = configure_animation(&game, game.mlx);
	if (FEATURE_FLAG_MINIMAP)
		init_minimap(&game);
	game_loop(&game);
	if (FEATURE_FLAG_MINIMAP)
		destroy_minimap(game.mlx, &game.minimap);
	destroy_sprite(game.mlx, game.animation.sprites, &game.animation);
	destroy_game(&game);
}
