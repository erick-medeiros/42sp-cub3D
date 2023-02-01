/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:13:36 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/01 19:57:09 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_bits(char *bytes, size_t num_bytes)
{
	size_t	i;
	short	j;

	i = 0;
	while (i < num_bytes)
	{
		j = 8;
		while (--j >= 0)
		{
			if (bytes[i] >> j & 0B00000001)
				printf("1");
			else
				printf("0");
		}
		++i;
	}
}

void	print_bits_nl(char *bytes, size_t num_bytes)
{
	print_bits(bytes, num_bytes);
	printf("\n");
}
