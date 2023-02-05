/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:18:55 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/27 20:56:22 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

char	*__getstr(char spec, va_list ap);
int		__sharp(const char **fmt, va_list ap);
int		__plus(const char **fmt, va_list ap);
int		__minus(const char **fmt, va_list ap);
int		__dot(const char **fmt, va_list ap);
int		__space(const char **fmt, va_list ap);
int		__zero(int n, const char **fmt, va_list ap);
int		__dot_dispatch(char spec, char *buff, va_list ap);
int		__minus_dispatch(char spec, char *buff, va_list ap);
int		__space_dispatch(char spec, char *buff, va_list ap);
int		__zero_dispatch(char spec, char *buff, va_list ap);
int		__spec_dispatch(char spec, va_list ap);
int		ft_printf(const char *fmt, ...);

#endif
