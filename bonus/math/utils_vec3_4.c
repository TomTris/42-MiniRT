/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec3_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:15:46 by obrittne          #+#    #+#             */
/*   Updated: 2024/10/02 17:46:49 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

t_vec3	vec_reflect(t_vec3 vector, t_vec3 reflected_around)
{
	return (subtract(scale(reflected_around, 2.0 * \
	dot_product(vector, reflected_around) / \
	dot_product(vector, reflected_around)), vector));
}

t_vec3	vec_reflect_norm(t_vec3 vector, t_vec3 reflected_around)
{
	return (subtract(scale(reflected_around, \
	2.0 * dot_product(vector, reflected_around)), vector));
}
