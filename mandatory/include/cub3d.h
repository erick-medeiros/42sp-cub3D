/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:50:28 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/17 19:03:13 by eandre-f         ###   ########.fr       */
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

// core
int			game_setup(t_game *game);
int			game_loop(t_game *game);
int			destroy_game(t_game *game);

int			render(t_game *game);
void		render_map(t_game *game);

int			handle_keypress(int keycode, t_game *game);
int			handle_keyrelease(int keycode, t_game *game);

// canvas
t_img		*create_canvas(void *mlx, int width, int height);
t_img		*create_canvas_texture(void *mlx, char *filename);
void		*destroy_canvas(void *mlx, t_img *canvas);
void		mlx_put_image_pixel(t_img *img, int x, int y, int argb_color);
t_argb		mlx_get_argb_image_pixel(t_img *img, int x, int y);

// draw
void		draw_background(t_img *img, int color);
void		draw_rectangle(t_img *img, t_rect rect, int argb_color);
void		draw_texture_on_canvas(t_game *game, t_img *texture);

// color
t_argb		create_argb_color(int a, int r, int g, int b);
t_argb		separate_argb_color(int argb);

// raycaster
void		raycaster(t_game *game);

// validation
int			input_validation(int ac, char **av);

// parsing
int			init_map(t_game *game, char **av);

// utils - vector
t_vector	create_vector(double x, double y);
t_vector	add_vector(t_vector v1, t_vector v2);
t_vector	sub_vector(t_vector v1, t_vector v2);
t_vector	mult_vector_vector(t_vector v1, t_vector v2);
t_vector	mult_vector_scalar(t_vector v1, double scalar);
double		mag_vector(t_vector v);
t_vector	normalize_vector(t_vector v1);
double		dot_product_of_vector(t_vector v1, t_vector v2);
double		angle_between_vectors(t_vector v1, t_vector v2);
t_vector	rotate_vector(t_vector v, double angle_radian);

// debug - utils
int			perr(const char *str);
void		debug_map(char **map);
int			is_reserved_ch(char c, const char *set);

#endif
