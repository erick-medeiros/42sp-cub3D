/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 18:02:17 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"
#include "parser.h"
#include "minimap.h"

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
	game_loop(&game);
	destroy_game(&game);
}
