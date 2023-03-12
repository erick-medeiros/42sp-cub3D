/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 19:56:33 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 17:32:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_rgb_color_params(t_game *game, char **colors, char id)
{
	if (id == 'F')
	{
		game->params.floor.r = ft_strtrim(colors[0], "\n\t");
		game->params.floor.g = ft_strtrim(colors[1], "\n\t");
		game->params.floor.b = ft_strtrim(colors[2], "\n\t");
	}
	else if (id == 'C')
	{
		game->params.ceil.r = ft_strtrim(colors[0], "\n\t");
		game->params.ceil.g = ft_strtrim(colors[1], "\n\t");
		game->params.ceil.b = ft_strtrim(colors[2], "\n\t");
	}
}

static int	is_color_present(char **colors)
{
	int	size;

	size = -1;
	while (colors[++size])
		continue ;
	if (size != 3)
	{
		ft_free_matrix(colors);
		return (perr("missing color"));
	}
	if (!ft_strncmp(colors[0], "\n", 2)
		|| !ft_strncmp(colors[1], "\n", 2)
		|| !ft_strncmp(colors[2], "\n", 2))
	{
		ft_free_matrix(colors);
		return (perr("missing color"));
	}
	return (1);
}

static int	init_color_scheme(t_game *game, char id, char *arg)
{
	char	**colors;
	int		count;
	int		i;

	i = -1;
	count = 0;
	while (arg[++i])
		if (arg[i] == ',')
			count++;
	if (count != 2)
		return (perr("invalid color schema"));
	colors = ft_split(arg, ',');
	if (!colors)
		return (0);
	if (!is_color_present(colors))
		return (0);
	init_rgb_color_params(game, colors, id);
	ft_free_matrix(colors);
	if (!validate_colors(game, id))
		return (0);
	return (1);
}

int	check_rgb_color(t_game *game, char *row, char ch, char *err_msg)
{
	char	**matrix;
	char	*id;

	matrix = get_matrix(row);
	if (!matrix)
		return (0);
	id = matrix[0];
	if (ft_strlen(id) != 1)
	{
		ft_free_matrix(matrix);
		return (perr("invalid identifier"));
	}
	if (!matrix[1])
	{
		ft_free_matrix(matrix);
		return (perr(err_msg));
	}
	if (!init_color_scheme(game, ch, matrix[1]))
	{
		ft_free_matrix(matrix);
		return (0);
	}
	ft_free_matrix(matrix);
	return (1);
}
