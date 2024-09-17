/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:59:01 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/17 20:43:46 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double	int_double_notvalid(char *str, int seen, int seen_other)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
		{
			if (str[i] == '.')
			{
				if (seen == 1 || seen_other == 0)
					return (2);
				seen = 1;
			}
			else if (str[i] == '+' || str[i] == '-')
			{
				if (seen_other)
					return (2);
			}
			else
				return (2);
		}
		else
			seen_other = 1;
	}
	return (seen);
}


int	get_sign(char *str, int *move)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '+' || str[i] != '-')
			break ;
		if (str[i] == '-')
			counter++;
		i++;
	}
	*move = i;
	if (counter % 2)
		return (-1);
	return (1);
}


long long	str_to_long_long(char *str)
{
	long long	out;
	int			i;

	out = 0;
	while (str[i])
	{
		out = out * 10 + str[i] - '0';
		i++;
	}
	return (out);
}


double	str_to_double(char *str)
{
	double	out;
	double	multiplier;
	int		seen;
	int		i;

	multiplier = 0.1;
	out = 0;
	seen = 0;
	while (str[i])
	{
		if (!seen)
		{
			if (str[i] == '.')
				seen = 1;
			else
				out = out * 10.0 + (double)(str[i] -' 0');
		}
		else
		{
			out += ((double)(str[i] -' 0') * multiplier);
			multiplier /= 10.0;
		}
	}
	return (out);
}
