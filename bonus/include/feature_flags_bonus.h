/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feature_flags_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:28:53 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 17:33:27 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FEATURE_FLAGS_BONUS_H
# define FEATURE_FLAGS_BONUS_H

// render minimap
# ifndef FEATURE_FLAG_MINIMAP
#  define FEATURE_FLAG_MINIMAP 1
# endif

// frame rate
# ifndef FEATURE_FLAG_FPS
#  define FEATURE_FLAG_FPS 1
# endif

// frame rate
# ifndef FEATURE_FLAG_MOUSE
#  define FEATURE_FLAG_MOUSE 1
# endif

// frame rate
# ifndef FEATURE_FLAG_COLLISION
#  define FEATURE_FLAG_COLLISION 1
# endif

# ifndef FEATURE_FLAG_DOOR
#  define FEATURE_FLAG_DOOR 1
# endif

# ifndef FEATURE_FLAG_ANIMATION
#  define FEATURE_FLAG_ANIMATION 1
# endif

#endif
