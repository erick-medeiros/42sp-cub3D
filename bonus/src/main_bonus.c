/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 17:35:43 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "feature_flags_bonus.h"
#include "parser_bonus.h"
#include "minimap_bonus.h"

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
	if (FEATURE_FLAG_ANIMATION)
		init_animation(&game);
	if (FEATURE_FLAG_MINIMAP)
		init_minimap(&game);
	game_loop(&game);
	if (FEATURE_FLAG_MINIMAP)
		destroy_minimap(game.mlx, &game.minimap);
	if (FEATURE_FLAG_ANIMATION)
		destroy_animation(&game, game.animation.sprites, &game.animation);
	destroy_game(&game);
}
