/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 21:17:23 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 17:32:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_map_size(t_game *game)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (game->map[++i])
		if (game->map[i][0] != '\n')
			len++;
	return (len);
}
