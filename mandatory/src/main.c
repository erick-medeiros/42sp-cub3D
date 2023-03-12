/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/11 21:39:05 by eandre-f         ###   ########.fr       */
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
	sprite->pos = create_vector(5.5, 4.5);
}

void	destroy_sprite(void *mlx, t_sprite *sprite)
{
	sprite->num_texture = 0;
	while (sprite->textures && sprite->textures[sprite->num_texture])
	{
		sprite->textures[sprite->num_texture] = destroy_canvas(mlx,
				sprite->textures[sprite->num_texture]);
		sprite->num_texture++;
	}
	free(sprite->textures);
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
	configure_sprite(game.mlx, &game.sprite);
	if (FEATURE_FLAG_MINIMAP)
		init_minimap(&game);
	game_loop(&game);
	if (FEATURE_FLAG_MINIMAP)
		destroy_minimap(game.mlx, &game.minimap);
	destroy_sprite(game.mlx, &game.sprite);
	destroy_game(&game);
}
