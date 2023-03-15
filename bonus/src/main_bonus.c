/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:05:05 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/15 03:14:10 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
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
	if (!game_setup(&game))
	{
		destroy_partial_game(&game);
		return (1);
	}
	game_loop(&game);
	destroy_game(&game);
}
