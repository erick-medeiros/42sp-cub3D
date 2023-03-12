/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:52:50 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/11 22:56:16 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "feature_flags.h"
#include "door.h"

int	init_config_params_with_door(t_game *game, char *filepath)
{
	char	*row;
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (!fd)
		return (0);
	if (FEATURE_FLAG_DOOR)
	{
		if (!validate_identifiers_with_door(filepath))
			return (perr("invalid identifier"));
	}
	else if (!validate_identifiers(filepath))
		return (perr("invalid identifier"));
	row = ft_gnl(fd);
	if (!row)
		return (0);
	while (row && is_reserved_ch(*row, "NSEWFCDA\n"))
	{
		if (is_empty_line(&row, fd))
			continue ;
		if (!validate_parameter(game, &row, fd))
			return (0);
	}
	return (validate_parameters_state(game, row, fd));
}

char	*get_map_with_door(int fd, int *map_width, int *map_height)
{
	char	*row;
	char	*buff;
	char	*tmp;

	row = ft_gnl(fd);
	if (!row)
		return (NULL);
	while (is_reserved_ch(*row, "NSEWCFDA\n"))
		if (!is_row_empty(&row, fd))
			return (NULL);
	buff = ft_strdup("");
	while (row)
	{
		if (ft_strlen(row) > 1)
			(*map_height)++;
		(*map_width) = fmaxf(*map_width, ft_strlen(row));
		tmp = buff;
		buff = ft_strjoin(buff, row);
		free(tmp);
		free(row);
		row = ft_gnl(fd);
	}
	(*map_width) = fmaxf(*map_width - 1, 0);
	return (buff);
}
