/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:14:29 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/04 15:07:08 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map_structure(t_game *game)
{
	char	*line;
	int		i;

	i = -1;
	while (++i < game->map_height)
	{
		line = ft_strtrim(game->map[i], " \n\t");
		if (ft_strlen(line) == 0)
		{
			if (line)
				free(line);
			continue ;
		}
		if (is_reserved_ch(*line, "NSWE"))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	print_map(game->map);

	if (!is_valid_map_structure(game))
		return (perr("[-] invalid map structure"));
	if (!validate_sides(game))
		return (0);
	return (1);
}
