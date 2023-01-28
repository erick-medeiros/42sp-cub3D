/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_extra.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 10:32:07 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/28 10:33:02 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_EXTRA_H
# define MLX_EXTRA_H

int	mlx_keypress_hook(void *win_ptr, int (*funct_ptr)(), void *param);
int	mlx_keyrelease_hook(void *win_ptr, int (*funct_ptr)(), void *param);
int	mlx_destroynotify_hook(void *win_ptr, int (*funct_ptr)(), void *param);

#endif
