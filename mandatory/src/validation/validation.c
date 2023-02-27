/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:47:13 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/02/27 11:45:16 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_file_extension(char *filename)
{
	int	offset;

	if (!ft_strrchr(filename, '.'))
		return (0);
	offset = ft_strlen(filename) - 4;
	if (ft_strncmp(".cub", filename + offset, 5) == 0)
		return (1);
	return (0);
}

static int	is_valid_input(int ac, char **av)
{
	int	fd;

	if (ac < 2)
		return (perr("[-] no map specified"));
	if (ac > 2)
		return (perr("[-] multiples arguments"));
	if (!is_valid_file_extension(av[1]))
		return (perr("[-] invalid map extension"));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (perr("[-] map doesnt exist or incorrect permissions"));
	close(fd);
	return (1);
}

int	input_validation(t_game *game, int ac, char **av)
{
	if (!is_valid_input(ac, av))
		return (0);
	if (!init_config_params(game, av[1]))
		return (0);
	return (1);
}
