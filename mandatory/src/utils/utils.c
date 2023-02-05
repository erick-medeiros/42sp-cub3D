/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:33:15 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/02/05 15:04:12 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_reserved_ch(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

int	perr(const char *str)
{
	if (str)
		printf("%s\n", str);
	return (0);
}
