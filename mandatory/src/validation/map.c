/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:14:29 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/05 18:07:34 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map(t_game *game, char *filepath)
{
	if (!validate_map_lines(filepath))
		return (0);
	if (!validate_sides(game))
		return (0);
	if (!validate_inner(game))
		return (0);
	return (1);
}
