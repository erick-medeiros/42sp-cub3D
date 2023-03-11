/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/11 12:48:18 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"
#include "parser.h"
#include "minimap.h"

#define FOX1 "./assets/fox/b1.xpm"
#define FOX2 "./assets/fox/b2.xpm"
#define FOX3 "./assets/fox/b3.xpm"
#define FOX4 "./assets/fox/b4.xpm"
#define FOX5 "./assets/fox/b5.xpm"
#define FOX6 "./assets/fox/b6.xpm"
#define FOX7 "./assets/fox/b7.xpm"
#define FOX8 "./assets/fox/b8.xpm"
#define FOX9 "./assets/fox/b9.xpm"

void	configure_sprite(void *mlx, t_sprite *sprite)
{
	sprite->textures = ft_calloc(10, sizeof(t_img *));
	sprite->textures[0] = create_canvas_texture(mlx, FOX1);
	sprite->textures[1] = create_canvas_texture(mlx, FOX2);
	sprite->textures[2] = create_canvas_texture(mlx, FOX3);
	sprite->textures[3] = create_canvas_texture(mlx, FOX4);
	sprite->textures[4] = create_canvas_texture(mlx, FOX5);
	sprite->textures[5] = create_canvas_texture(mlx, FOX6);
	sprite->textures[6] = create_canvas_texture(mlx, FOX7);
	sprite->textures[7] = create_canvas_texture(mlx, FOX8);
	sprite->textures[8] = create_canvas_texture(mlx, FOX9);
	sprite->num_texture = 0;
	sprite->frames = 0;
	sprite->pos = create_vector(5.5, 4.5);
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
	destroy_game(&game);
}
