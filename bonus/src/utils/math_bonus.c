/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:19:25 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/11 15:49:59 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_max(int number1, int number2)
{
	if (number2 > number1)
		return (number2);
	else
		return (number1);
}

int	ft_min(int number1, int number2)
{
	if (number2 < number1)
		return (number2);
	else
		return (number1);
}

int	ft_constrain(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}
