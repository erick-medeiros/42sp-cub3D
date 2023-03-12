/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:48:48 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 17:32:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	print_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (is_reserved_ch(map[i][j], "NSEW"))
				printf(FG_RED BG_BLUE "%c" RES, map[i][j]);
			else if (map[i][j] == ' ')
				printf(BG_YELLOW "%c" RES, ' ');
			else if (!is_reserved_ch(map[i][j], "0123 NSEW"))
				printf(BG_RED "%c" RES, map[i][j]);
			else if (map[i][j] == '1')
				printf(BG_GREEN_W "%c" RES, map[i][j]);
			else if (map[i][j] == '0')
				printf(BG_GREEN_F "%c" RES, map[i][j]);
			else
				printf(BG_PURPLE "%c" RES, map[i][j]);
		}
		printf("\n");
	}
}
