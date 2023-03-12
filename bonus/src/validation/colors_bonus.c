/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 20:18:26 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 17:32:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_valid_rgb(t_game *game)
{
	int	r;
	int	g;
	int	b;

	r = game->ceilling_color.r;
	g = game->ceilling_color.g;
	b = game->ceilling_color.b;
	if (r == -1 && g == -1 && b == -1)
		return (0);
	r = game->floor_color.r;
	g = game->floor_color.g;
	b = game->floor_color.b;
	if (r == -1 && g == -1 && b == -1)
		return (0);
	return (1);
}

static int	is_valid_color_range(int r, int g, int b)
{
	if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255))
		return (1);
	return (0);
}

static int	is_color_numeric(t_game *game, char id)
{
	char	*r;
	char	*g;
	char	*b;

	if (id == 'F')
	{
		r = game->params.floor.r;
		g = game->params.floor.g;
		b = game->params.floor.b;
		if (!is_digit_string(r) || !is_digit_string(g) || !is_digit_string(b))
			return (0);
	}
	else if (id == 'C')
	{
		r = game->params.ceil.r;
		g = game->params.ceil.g;
		b = game->params.ceil.b;
		if (!is_digit_string(r) || !is_digit_string(g) || !is_digit_string(b))
			return (0);
	}
	return (1);
}

static int	assign_color_value(t_game *game, t_argb *place,
	t_colors colors, char id)
{
	int	r;
	int	g;
	int	b;

	if (!is_color_numeric(game, id))
		return (perr("color value must be a positive digit"));
	r = ft_atoi(colors.r);
	g = ft_atoi(colors.g);
	b = ft_atoi(colors.b);
	if (!is_valid_color_range(r, g, b))
		return (perr("color value range should be between 0-255"));
	*place = create_argb_color(0, r, g, b);
	return (1);
}

int	validate_colors(t_game *game, char id)
{
	if (id == 'F')
		return (assign_color_value(game, &game->floor_color,
				game->params.floor, id));
	else if (id == 'C')
		return (assign_color_value(game, &game->ceilling_color,
				game->params.ceil, id));
	return (1);
}
