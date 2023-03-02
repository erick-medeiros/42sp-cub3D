/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 21:17:23 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/01 20:33:42 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_map_attribute(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (!is_reserved_ch(map[i][j], "01 NSEWFC\t\n"))
				return (0);
	}
	return (1);
}

int	is_valid_map(char **map)
{
	if (!is_player_found(map))
		return (perr("[-] invalid number of players"));
	if (!is_valid_map_attribute(map))
		return (perr("[-] invalid map attribute"));
	return (1);
}
