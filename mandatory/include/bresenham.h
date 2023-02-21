/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:29:42 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/21 00:56:28 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRESENHAM_H
# define BRESENHAM_H

# include "cub3d.h"

typedef struct s_bpoint {
	int	x;
	int	y;
}	t_bpoint;

typedef struct s_bresenham {
	t_bpoint	p1;
	t_bpoint	p2;
	int			xi;
	int			yi;
	int			delta_x;
	int			delta_y;
	int			error;
}	t_bresenham;

void	bresenham_axis(t_bresenham *b, t_img *img, int color);
void	bresenham_octante_1_5(t_bresenham *b, t_img *img, int color);
void	bresenham_octante_8_4(t_bresenham *b, t_img *img, int color);
void	bresenham_octante_2_6(t_bresenham *b, t_img *img, int color);
void	bresenham_octante_7_3(t_bresenham *b, t_img *img, int color);

#endif
