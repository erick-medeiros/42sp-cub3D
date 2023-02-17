/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:09:29 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/17 13:11:10 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "cub3d.h"
# include <stddef.h>
# include <stdio.h>

void	print_bits(char *bytes, size_t num_bytes);
void	print_bits_nl(char *bytes, size_t num_bytes);
void	debug_vector(char *name, t_vector vector);

#endif
