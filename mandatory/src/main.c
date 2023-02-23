/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/23 09:24:27 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"
#include "parser.h"

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
	if (FEATURE_FLAG_PENGUIN)
		game.north_texture = create_canvas_texture(game.mlx, IMG_XPM);
	if (FEATURE_FLAG_MINIMAP)
		init_minimap(&game);
	game.floor_color = separate_argb_color(COLOR_2);
	game.ceilling_color = separate_argb_color(COLOR_3);
	game_loop(&game);
	if (FEATURE_FLAG_MINIMAP)
		destroy_canvas(game.mlx, game.minimap.frame);
	destroy_game(&game);
}
