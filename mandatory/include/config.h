/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:05:21 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/11 11:43:23 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

// window settings
# define WINDOW_NAME "cub3D"
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768

// player moves
# define FOV_RAD 0.66
# define MOVEMENT_SPEED 0.04
# define STRAFE_SPEED 0.04
# define ROTATE_SPEED_RAD 0.04

// max map size
# define MAX_MAP_SIZE 100

// collision
# define DIST_TO_WALL 0.3

#endif
