/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 21:55:07 by qdo               #+#    #+#             */
/*   Updated: 2024/10/01 21:58:12 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// type_cy == 1 side  type_cy == 2 bottom  3 top

t_vec3	apply_texture_cylinder(t_hit *hit)
{
	t_vec3	midle_top = scale(hit.c)
	hit->cylinder;
	// hit->type_cy == 1;
	hit->world_position = p;
}