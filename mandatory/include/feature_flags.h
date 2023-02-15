/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feature_flags.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:28:53 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/14 22:13:22 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FEATURE_FLAGS_H
# define FEATURE_FLAGS_H

// render map
# ifndef FEATURE_FLAG_RENDER_MAP
#  define FEATURE_FLAG_RENDER_MAP 0
# endif

// raycaster
# ifndef FEATURE_FLAG_RAYCASTER
#  define FEATURE_FLAG_RAYCASTER 1
# endif

# define RAYCASTER_WIDTH 320
# define RAYCASTER_HEIGHT 200
# define RAYCASTER_MAP_BLOCK 10

#endif
