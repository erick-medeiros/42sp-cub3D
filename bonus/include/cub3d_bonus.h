/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:50:28 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/15 03:23:56 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "data_types_bonus.h"
# include "config_bonus.h"
# include <X11/X.h>      // X11 events
# include <fcntl.h>      // open
# include <libft.h>      // lib: libft
# include <math.h>       // lib: math
# include <mlx.h>        // lib: minilibx
# include <stdio.h>      // printf, perror
# include <stdlib.h>     // malloc, free, exit
# include <string.h>     // strerror
# include <unistd.h>     // close, read, write
# include "colors_bonus.h"

// core
void		game_init(t_game *game);
int			game_setup(t_game *game);
int			game_loop(t_game *game);
int			destroy_game(t_game *game);
int			destroy_partial_game(t_game *game);

int			render(t_game *game);

int			handle_keypress(int keycode, t_game *game);
int			handle_keyrelease(int keycode, t_game *game);
int			handle_mouse_move(int x, int y, t_game *game);
int			handle_mouse_press(int button, int x, int y, t_game *game);
int			handle_mouse_release(int button, int x, int y, t_game *game);
void		input_handler(t_game *game);

void		init_player(t_game *game);
void		init_params(t_game *game);
void		clean_params(t_params *params);
void		clean_canvas(t_game *game);
int			init_textures(t_game *game);
void		player_orientation(t_player *player, char orientation);

// canvas
t_img		*create_canvas(void *mlx, int width, int height);
t_img		*create_canvas_texture(void *mlx, char *filename);
void		save_canvas_background(t_img *canvas);
void		reset_canvas(t_img *canvas);
void		*destroy_canvas(void *mlx, t_img *canvas);
void		mlx_put_image_pixel(t_img *img, int x, int y, int argb_color);
t_argb		mlx_get_argb_image_pixel(t_img *img, int x, int y);
void		mlx_copy_image_pixel(t_img *dst, t_px dst_px, t_img *src,
				t_px src_px);

// draw
void		draw_line(t_img *img, t_vector p1, t_vector p2, int argb_color);
void		draw_background(t_img *img, int color);
void		draw_rectangle(t_img *img, t_rect rect, int argb_color);
void		draw_ceiling(t_img *img, int argb_color);
void		draw_floor(t_img *img, int argb_color);
void		draw_layer(t_img *canvas, t_img *layer,
				t_px start_canvas, t_px start_layer);
void		draw_layer_scale(t_img *canvas, t_img *layer, t_vector init,
				double scale);
void		draw_layer_fullscreen(t_img *canvas, t_img *layer, double *scale,
				t_px *pixel);

// color
t_argb		create_argb_color(int a, int r, int g, int b);
t_argb		separate_argb_color(int argb);

// raycaster
void		raycaster(t_game *game, t_img *img);

// validation
void		clean_gnl(char *tmp, int fd);
int			input_validation(t_game *game, int ac, char **av);
int			files_validation(t_params *params, char *filepath);
int			validation_failed(t_params *params);
char		**get_matrix(char *row);
char		*get_filename(char *filename);
int			validate_file(char *filepath);

int			validate_parameter(t_game *game, char **row, int fd);
int			is_valid_rgb(t_game *game);
int			validate_colors(t_game *game, char id);
int			validate_sides(t_game *game);
int			validate_map_lines(char *filepath);
int			validate_inner(t_game *game);
int			validate_parameters_state(t_game *game, char *row, int fd);

// parser
int			is_row_empty(char **row, int fd);
int			check_texture(t_game *game, char *row, char *cardinal,
				char *err_msg);
int			check_rgb_color(t_game *game, char *row, char ch, char *err_msg);
int			get_width_map(int width, char *row);

// utils
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
t_vector	set_mag_vector(t_vector v, double new_mag);
int			perr(char *str);
int			is_reserved_ch(char c, const char *set);
int			is_empty_line(char **row, int fd);
int			is_digit_string(char *str);
int			get_map_size(t_game *game);
double		calcule_scale(int origin_width, int origin_height,
				int destination_width, int destination_height);
int			clean_map(t_game *game);
char		*start_map(t_game *game, int fd);

int			ft_max(int number1, int number2);
int			ft_min(int number1, int number2);
int			ft_constrain(int value, int min, int max);
int			is_door_open(t_game *game);
int			is_valid_bonus_textures(t_game *game);

// debug
void		print_map(char **map);

void		init_animation(t_game *game);
void		get_door_side_texture(t_game *game);
int			count_char_in_map(t_game *game, char c);
void		load_sprite(t_game *game, t_sprite *sprite);
void		destroy_animation(t_game *game, t_sprite *sprites,
				t_animation *animation);

#endif
