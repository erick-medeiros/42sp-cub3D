/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/16 10:28:40 by eandre-f         ###   ########.fr       */
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

	if (FEATURE_FLAG_RAYCASTER)
	{
		argc = 2;
		argv[1] = "maps/square_10x10.cub";
	}
	if (!input_validation(argc, argv))
		return (1);
	if (!init_map(&game, argv))
		return (1);
	game_setup(&game);
	game.north_texture = create_canvas_texture(game.mlx, IMG_XPM);
	if (FEATURE_FLAG_RAYCASTER)
	{
		game._minimap = create_canvas(game.mlx, game.map_width,
				game.map_height);
		game._raycast = create_canvas(game.mlx, 320, 200);
	}
	game.floor_color = separate_argb_color(COLOR_2);
	game.ceilling_color = separate_argb_color(COLOR_3);
	game_loop(&game);
	destroy_game(&game);
}
