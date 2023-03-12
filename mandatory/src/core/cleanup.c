/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:06:41 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 16:48:51 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"

void	clean_params(t_params *params)
{
	if (!params)
		return ;
	free(params->north_texture);
	free(params->south_texture);
	free(params->east_texture);
	free(params->west_texture);
	free(params->floor.r);
	free(params->floor.g);
	free(params->floor.b);
	free(params->ceil.r);
	free(params->ceil.g);
	free(params->ceil.b);
}

void	clean_canvas(t_game *game)
{
	game->canvas = destroy_canvas(game->mlx, game->canvas);
	game->canvas = destroy_canvas(game->mlx, game->canvas);
	game->north_texture = destroy_canvas(game->mlx, game->north_texture);
	game->canvas = destroy_canvas(game->mlx, game->canvas);
	game->canvas = destroy_canvas(game->mlx, game->canvas);
	game->south_texture = destroy_canvas(game->mlx, game->south_texture);
	game->canvas = destroy_canvas(game->mlx, game->canvas);
	game->west_texture = destroy_canvas(game->mlx, game->west_texture);
	game->east_texture = destroy_canvas(game->mlx, game->east_texture);
	if (FEATURE_FLAG_DOOR)
	{
		game->door_texture = destroy_canvas(game->mlx, game->door_texture);
	}
}

int	destroy_game(t_game *game)
{
	clean_canvas(game);
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	clean_params(&game->params);
	ft_free_matrix(game->map);
	if (FEATURE_FLAG_DOOR && game->sprites.textures)
	{
		ft_free_matrix(game->sprites.textures);
		ft_free_matrix(game->door_sprites.textures);
	}
	game->map = NULL;
	free(game->animation.all_perpend);
	return (0);
}
