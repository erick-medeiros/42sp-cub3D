/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/27 21:02:22 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"
#include "parser.h"

int	main(int argc, char *argv[])
{
	t_game	game;

	game_init(&game);
	if (!input_validation(&game, argc, argv))
		return (1);
	if (!init_map(&game, argv))
		return (1);
	game.ceilling_color = separate_argb_color(0x00FFFF);
	game.floor_color = separate_argb_color(0xFF00FF);
	game_setup(&game);
	game.north_texture = create_canvas_texture(game.mlx, "assets/red.xpm");
	game.south_texture = create_canvas_texture(game.mlx, "assets/blue.xpm");
	game.west_texture = create_canvas_texture(game.mlx, "assets/green.xpm");
	game.east_texture = create_canvas_texture(game.mlx, "assets/yellow.xpm");
	if (FEATURE_FLAG_MINIMAP)
		init_minimap(&game);
	game_loop(&game);
	if (FEATURE_FLAG_MINIMAP)
		destroy_canvas(game.mlx, game.minimap.frame);
	destroy_game(&game);
}
