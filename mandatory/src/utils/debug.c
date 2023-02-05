/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:48:48 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/02/05 14:56:41 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug_map(char **map)
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
				printf("\e[46m%c\e[0m", map[i][j]);
			else if (map[i][j] == ' ')
				printf("%c", ' ');
			else if (!is_reserved_ch(map[i][j], "0123 NSEW"))
				printf("\e[45m%c\e[0m", map[i][j]);
			else
				printf("\e[41m%c\e[0m", map[i][j]);
		}
		printf("\n");
	}
}
