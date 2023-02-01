/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:20:23 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/31 21:24:33 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_argb	create_argb_color(int a, int r, int g, int b)
{
	t_argb	color;

	color.a = a;
	color.r = r;
	color.g = g;
	color.b = b;
	color.argb = (a << 24) | (r << 16) | (g << 8) | b;
	return (color);
}
