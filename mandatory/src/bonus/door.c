/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 03:56:01 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/11 15:53:55 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_attributes_with_door(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!is_reserved_ch(map[i][j], "01 NSEWFCD\t\n"))
				return (0);
		}
	}
	return (1);
}

int	validate_identifiers_with_door(char *filepath)
{
	char	*row;
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (!fd)
		return (0);
	row = ft_gnl(fd);
	if (!row)
		return (0);
	while (row)
	{
		if (!is_reserved_ch(*row, "NSEWFC10D \n"))
		{
			clean_gnl(row, fd);
			return (0);
		}
		free(row);
		row = ft_gnl(fd);
	}
	return (1);
}

void	open_door_and_update_matrix(t_game *game)
{
	if (game->map[(int)game->player.pos.y - 1][(int)game->player.pos.x] == 'D')
		game->map[(int)game->player.pos.y - 1][(int)game->player.pos.x] = '0';
	if (game->map[(int)game->player.pos.y + 1][(int)game->player.pos.x] == 'D')
		game->map[(int)game->player.pos.y + 1][(int)game->player.pos.x] = '0';
	if (game->map[(int)game->player.pos.y][(int)game->player.pos.x - 1] == 'D')
		game->map[(int)game->player.pos.y][(int)game->player.pos.x - 1] = '0';
	if (game->map[(int)game->player.pos.y][(int)game->player.pos.x + 1] == 'D')
		game->map[(int)game->player.pos.y][(int)game->player.pos.x + 1] = '0';
}

int	check_door_texture(t_game *game, char *row)
{
	char	**tokens;

	tokens = get_matrix(row);
	if (!tokens)
		return (0);
	if (!tokens[1])
	{
		ft_free_matrix(tokens);
		return (0);
	}
	game->params.door_texture = ft_strtrim(tokens[1], " \n\t");
	ft_free_matrix(tokens);
	return (1);
}
