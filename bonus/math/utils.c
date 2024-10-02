/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:32:18 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 18:21:52 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

double	dot_product_d(double *vec1, double *vec2)
{
	return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}

double	get_len_vector_d(double *vector)
{
	return (sqrt(dot_product_d(vector, vector)));
}

void	normilize_vector_d(double *vec)
{
	double	len;

	len = get_len_vector_d(vec);
	vec[0] /= len;
	vec[1] /= len;
	vec[2] /= len;
}

double	max_double(double v1, double v2)
{
	if (v1 > v2)
		return (v1);
	return (v2);
}

double	min_double(double v1, double v2)
{
	if (v1 < v2)
		return (v1);
	return (v2);
}
