/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.checker2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:43:23 by qdo               #+#    #+#             */
/*   Updated: 2024/09/27 23:02:53 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abc.h"

static int	is_two_vector_same_direction3(t_vec3 vec1, t_vec3 vec2,
	double rate, int rate_defind)
{
	if (vec1.z == 0 || vec2.z == 0)
	{
		if (vec1.z != vec2.z)
			return (0);
		if (vec1.z * vec2.z > 0)
			return (1);
		return (0);
	}
	else
	{
		if (rate_defind == 0)
			return (1);
		else if (rate != vec2.y / vec1.y)
			return (0);
		return (1);
	}
	perror("sth wrong in is_two_vector_same_direction");
	return (0);
}

static int	is_two_vector_same_direction2(t_vec3 vec1, t_vec3 vec2,
	double rate, int rate_defind)
{
	if (vec1.y == 0 || vec2.y == 0)
	{
		if (vec1.y != vec2.y)
			return (0);
	}
	else
	{
		if (rate_defind == 0)
		{
			rate_defind = 1;
			rate = vec2.y / vec1.y;
		}
		else if (rate != vec2.y / vec1.y)
			return (0);
	}
	return (is_two_vector_same_direction3(vec1, vec2, rate, rate_defind));
}

int	is_two_vector_same_direction(t_vec3 vec1, t_vec3 vec2)
{
	double	rate;
	int		rate_defind;

	rate = 0;
	rate_defind = 0;
	if (vec1.x == 0 || vec2.x == 0)
	{
		if (vec1.x != vec2.x)
			return (0);
	}
	else
	{
		rate_defind = 1;
		rate = vec2.x / vec1.x;
	}
	return (is_two_vector_same_direction2(vec1, vec2, rate, rate_defind));
}

static t_vec3	vector_AO_form_A_O(t_point pA, t_point pO)
{
	t_vec3	ret;

	ret.x = pO.x - pA.x;
	ret.y = pO.y - pA.y;
	ret.z = pO.z - pA.z;
	return (ret);
}

int	is_valid_cone(t_cone cone)
{
	t_vec3	vAO;

	vAO = vector_AO_form_A_O(cone.pA, cone.pO);
	if (is_valid_vector(cone.vAO) && is_valid_vector(vAO) && cone.r > 0 \
		&& is_two_vector_same_direction(cone.vAO, vAO))
		return (1);
	return (0);
}
