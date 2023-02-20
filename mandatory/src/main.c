/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/19 21:02:31 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"

#define IMG_XPM "assets/penguin.xpm"
#define COLOR_1 0xFFFF90
#define COLOR_2 0xFF00FF
#define COLOR_3 0x00FFFF

int	main(int argc, char *argv[])
{
	t_game	game;

	if (!input_validation(argc, argv))
		return (1);
	if (!init_map(&game, argv))
		return (1);
	game_setup(&game);
	game.north_texture = create_canvas_texture(game.mlx, IMG_XPM);
	if (FEATURE_FLAG_RAYCASTER)
	{
		game.player.plane = create_vector(0.66, 0);
		game.player.pos = create_vector(5, 5);
		game.player.dir = create_vector(0, -1);
		game._minimap = create_canvas(game.mlx, game.map_width,
				game.map_height);
		game._engine = create_canvas(game.mlx, 320, 200);
	}
	game.floor_color = separate_argb_color(COLOR_2);
	game.ceilling_color = separate_argb_color(COLOR_3);
	game_loop(&game);
	destroy_game(&game);
}
