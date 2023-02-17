/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:29:42 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/17 18:40:21 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRESENHAM_H
# define BRESENHAM_H

# include "cub3d.h"

typedef struct s_point {
	double	x;
	double	y;
}	t_point;

typedef struct s_bresenham {
	t_img		*img;
	t_point		p1;
	t_point		p2;
	int			color;
	int			xi;
	int			yi;
	int			delta_x;
	int			delta_y;
	int			error;
}	t_bresenham;

void	bresenham_octantes(t_bresenham *b);
void	bresenham(t_img *img, t_point *p1, t_point *p2, int color);

#endif
