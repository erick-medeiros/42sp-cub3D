/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:20:23 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/01 19:47:08 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_argb	create_argb_color(int a, int r, int g, int b)
{
	t_argb	color;

	color.a = a & 0xFF;
	color.r = r & 0xFF;
	color.g = g & 0xFF;
	color.b = b & 0xFF;
	color.argb = (a << 24) | (r << 16) | (g << 8) | b;
	return (color);
}
