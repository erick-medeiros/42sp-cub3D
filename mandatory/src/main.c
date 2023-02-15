/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/15 11:19:09 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"

#define IMG_XPM "assets/penguin.xpm"
#define COLOR_1 0xFFFF90
#define COLOR_2 0xFF00FF
#define COLOR_3 0x00FFFF

int	main(int ac, char **av)
{
	t_game	game;

	if (!input_validation(ac, av))
		return (1);
	if (!init_map(&game, av))
		return (1);
	game_setup(&game);
	game.north_texture = create_canvas_texture(game.mlx, IMG_XPM);
	if (FEATURE_FLAG_RAYCASTER)
	{
		game.west_texture = create_canvas(game.mlx,
				RAYCASTER_MAP_BLOCK, RAYCASTER_MAP_BLOCK);
		game.south_texture = create_canvas(game.mlx,
				RAYCASTER_WIDTH, RAYCASTER_HEIGHT);
	}
	game.floor_color = separate_argb_color(COLOR_2);
	game.ceilling_color = separate_argb_color(COLOR_3);
	game_loop(&game);
	destroy_game(&game);
}
