/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:50:28 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/05 15:16:41 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "data_types.h"
# include <X11/X.h>      // X11 events
# include <X11/keysym.h> // X11 keys
# include <fcntl.h>      // open
# include <libft.h>      // lib: libft
# include <math.h>       // lib: math
# include <mlx.h>        // lib: minilibx
# include <stdio.h>      // printf, perror
# include <stdlib.h>     // malloc, free, exit
# include <string.h>     // strerror
# include <unistd.h>     // close, read, write

int		handle_keypress(int keycode, t_game *game);
int		handle_keyrelease(int keycode, t_game *game);

// mlx images
int		init_mlx_image(void *mlx, t_mlx_img *img, int width, int height);
char	*mlx_get_image_pixel(t_mlx_img *img, int x, int y);
void	mlx_put_image_pixel(t_mlx_img *img, int x, int y, int argb_color);

// draw
void	draw_background(t_mlx_img *img, int color);
void	draw_rectangle(t_mlx_img *img, t_rect rect, int argb_color);

// color
t_argb	create_argb_color(int a, int r, int g, int b);

// validation
int		input_validation(int ac, char **av);

// parsing
int		init_map(t_game *game, char **av);

// debug - utils
int		perr(const char *str);
void	debug_map(char **map);
int		is_reserved_ch(char c, const char *set);

#endif
