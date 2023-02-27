/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/27 19:14:59 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"
#include "parser.h"

// #define IMG_XPM "assets/penguin.xpm"
#define IMG_XPM "assets/wolftex/pics_xpm/redbrick.xpm"
#define COLOR_1 0xFFFF90
#define COLOR_2 0xFF00FF
#define COLOR_3 0x00FFFF

int	main(int argc, char *argv[])
{
	t_game	game;

	game_init(&game);
	if (!input_validation(&game, argc, argv))
		return (1);
	if (!init_map(&game, argv))
		return (1);
	game_setup(&game);
	game.north_texture = create_canvas_texture(game.mlx, IMG_XPM);
	game.south_texture = create_canvas_texture(game.mlx, IMG_XPM);
	game.west_texture = create_canvas_texture(game.mlx, IMG_XPM);
	game.east_texture = create_canvas_texture(game.mlx, IMG_XPM);
	// if (FEATURE_FLAG_PENGUIN)
	// 	game.north_texture = create_canvas_texture(game.mlx, IMG_XPM);
	if (FEATURE_FLAG_MINIMAP)
		init_minimap(&game);
	game_loop(&game);
	if (FEATURE_FLAG_MINIMAP)
		destroy_canvas(game.mlx, game.minimap.frame);
	destroy_game(&game);
}
