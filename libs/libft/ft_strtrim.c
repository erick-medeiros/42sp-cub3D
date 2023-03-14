/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:36:43 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/13 20:57:56 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft__setoff(const char *set, const char ch)
{
	while (*set)
		if ((unsigned char)ch == (unsigned char)*set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*last;
	const char	*start;

	start = s1;
	last = s1 + (ft_strlen(s1) - 1);
	while (ft__setoff(set, *s1))
		s1++;
	while (last != start && ft__setoff(set, *last))
		last--;
	if (s1 > last)
		return (ft_strdup(""));
	return (ft_substr(s1, 0, (last - s1) + 1));
}
